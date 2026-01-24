#include <iostream>
// #include <llvm/IR/Module.h>
// #include <llvm/IR/IRBuilder.h>
// #include <llvm/IR/LLVMContext.h>
#include "lexer.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/ErrorOr.h"
int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Please provide input file.\n");
        return 0;
    }

    const char *FileName = argv[1];

    static llvm::ErrorOr<std::unique_ptr<llvm::MemoryBuffer>> file = llvm::MemoryBuffer::getFile(FileName);
    if (!file) {
        llvm::errs() << "Error reading file: " << FileName << "\n";
        return 0;
    }
    std::unique_ptr<llvm::MemoryBuffer> fileBuffer = std::move(*file);
    Lexer lex(fileBuffer->getBuffer());

    Token tok;
    while (tok.tokenType != TokenType::eof) {
        lex.NextToken(tok);
        tok.Dump();
    
    }
    return 1;
}
