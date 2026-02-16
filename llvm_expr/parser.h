#pragma once
#include "lexer.h"
class Parser {
    private:
        Lexer lexer;
    public:
        Parser(Lexer &lexer) : lexer(lexer) {};
};