#pragma once
#include "ast.h"
#include "parser.h"
class PrintVisitor : public Visitor {
public:
    PrintVisitor(std::shared_ptr<Program> program);
    // llvm::Value* VisitorExpr(Expr *expr) override;
    llvm::Value* VisitorBinaryExpr(BinaryExpr *binaryExpr) override;
    llvm::Value* VisitorFactorExpr(FactorExpr *factorExpr) override;
    llvm::Value* VisitorProgram(Program *program) override;
};