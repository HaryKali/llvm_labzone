#pragma once
#include<llvm/ADT/StringRef.h>
/// cahr stream -> token stream

enum class TokenType {
    unknow,
    number,
    plus,
    minus,
    slash,
    star,
    l_paren,
    r_paren,
    semi,
    eof, // end of file
};


class Token {
    public:
        int row, col;
        TokenType tokenType;
        int value; // only for number tokens

        Token(){
            row=col=-1;
            tokenType=TokenType::unknow;
            value=0;

        }
};  

class Lexer {
    public:
        Lexer(llvm::StringRef sourceCode);
        void NextToken(Token &tok);
    private:
        const char* BufPtr;
        const char* LineHeadPtr;
        const char* BufEnd;
};      