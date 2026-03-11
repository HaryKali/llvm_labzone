
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
std::shared_ptr<Expr> Parser::ParseTerm() {
    auto term=ParseTerm();


};
std::shared_ptr<Expr> Parser::ParseFactor() {

};

bool Parser::Expect(TokenType tokenType) {

};

bool Parser::Consume(TokenType tokenType) {

};

void Parser::Advance() {
    // lexer.NextToken(tok);
};