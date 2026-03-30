
// prog : (expr? ";")*
// expr : term (("+" | "-") term)* ;
// term : factor (("*" | "/") factor)* ;
// factor : number | "(" expr ")" ; // 1*(2+3)
// number: ([0-9])* ;


#include "parser.h"

std::shared_ptr<Program> Parser::ParseProgram() {
    // while Ture .....EXIT
    // token->eof
    std::vector<std::shared_ptr<Expr>> exprVec;
    while (tok.tokenType != TokenType::eof) {
        // parse expr
        // expect ';'
        if (tok.tokenType == TokenType::semi) {
            Advance();
            continue;
        }
        auto expr = ParseExpr();
        exprVec.push_back(expr);

    }
    auto program=std::make_shared<Program>();
    program->exprs = std::move(exprVec);
    return program;
};

// left combining

// expr : term (("+" | "-") term)* ;
std::shared_ptr<Expr> Parser::ParseExpr(){
    auto left =ParseTerm();

    while (tok.tokenType == TokenType::plus || tok.tokenType == TokenType::minus) {
        OPCode op;
        if (tok.tokenType == TokenType::plus) {
            op = OPCode::ADD;
        } else {
            op = OPCode::SUB;
        }
        Advance();
        auto BinaryExpr = std::make_shared<BinaryExpr>();
        BinaryExpr->op = op;
        BinaryExpr->left = left;
        BinaryExpr->right = ParseTerm();

        left=BinaryExpr;

    }
    return left;
} 

// left combining can be optimized by right combining, but it is more complex to implement, 
//and the performance improvement is not significant, so we use left combining here.
// term : factor (("*" | "/") factor)* ;
std::shared_ptr<Expr> Parser::ParseTerm() {

    auto left =ParseFactor();
    while (tok.tokenType == TokenType::star || tok.tokenType == TokenType::slash) {
        OPCode op;
        if (tok.tokenType == TokenType::star) {
            op = OPCode::MUL;
        } else {
            op = OPCode::DIV;
        }
        Advance();
        auto BinaryExpr = std::make_shared<BinaryExpr>();
        BinaryExpr->op = op;
        BinaryExpr->left = left;
        BinaryExpr->right = ParseFactor();

        left=BinaryExpr;

    }
    return left;

};
// term : factor (("*" | "/") factor)* ;
std::shared_ptr<Expr> Parser::ParseFactor() {
    if (tok.tokenType == TokenType::l_parent) {
        Advance();
        auto expr=ParseExpr();
        assert(tok.tokenType == TokenType::r_parent);
        Advance();
        return expr;
    } else{
        auto factor=std::make_shared<FactorExpr>();
        factor->number=tok.value;
        Advance();
        return factor;  

    }

};

bool Parser::Expect(TokenType tokenType) {
    if (tok.tokenType == tokenType) {
        return true;
    } else {
        llvm::errs() << "Error: Expected token type " << static_cast<int>(tokenType) << " but got " << static_cast<int>(tok.tokenType) << " at row " << tok.row << ", col " << tok.col << "\n";
        return false;
    }
};

bool Parser::Consume(TokenType tokenType) {
    if (Expect(tokenType)) {
        Advance();
        return true;
    } else {
        return false;
    }
};

void Parser::Advance() {
    lexer.NextToken(tok);
};