#pragma once
#include "ast.h"
#include "parser.h"
class PrintVisitor : public Visitor {
public:
    PrintVisitor(std::shared_ptr<Program> program);
    void VisitorBinaryExpr(BinaryExpr *binaryExpr) override;
    void VisitorFactorExpr(FactorExpr *factorExpr) override;
    void VisitorProgram(Program *program) override;
};