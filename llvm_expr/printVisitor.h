#pragma once
#include "ast.h"
#include "parser.h"
class PrintVisitor: public Visitor{
    public:
        void VisitBinaryExpr(BinaryExpr *binaryExpr) override;
        void VisitFactorExpr(FactorExpr *factorExpr) override;
        void VisitProgram(Program *program) override;
};