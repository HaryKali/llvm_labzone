#pragma once
#include "lexer.h"
#include "ast.h"
class Parser {
    private:
        Lexer lexer;
        std::shared_ptr<Expr> ParseTerm();
        std::shared_ptr<Expr> ParseFactor();
    public:
        Parser(Lexer &lexer) : lexer(lexer) {};
        std::shared_ptr<Program> ParseProgram();


    //Check if the next token is of the expected type.
    bool Expect(TokenType tokenType);
    
    // Check and consume the next token if it matches the expected type. If it does not match, it should report an error.
    bool Consume(TokenType tokenType);
    //Advnac
    void Advance();

    Token tok;

};