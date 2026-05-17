#pragma once
#include <memory>
#include<vector>
#include "llvm/IR/Value.h"
class Program;
class Expr;
class BinaryExpr;
class FactorExpr;
class Visitor{
    public:
        virtual ~Visitor(){};
        virtual llvm::Value* VisitorProgram(Program *p) = 0;
        virtual llvm::Value* VisitorExpr(Expr *expr) { return nullptr; }
        virtual llvm::Value* VisitorBinaryExpr(BinaryExpr *expr) = 0;
        virtual llvm::Value* VisitorFactorExpr(FactorExpr *expr) = 0;
};

class Expr{
    public:
        virtual ~Expr(){};
        virtual llvm::Value* Accept(Visitor* visitor){return nullptr;};

};

enum class OPCode{
    ADD,
    SUB,
    MUL,
    DIV

};

class BinaryExpr: public Expr{
    public:
        ~BinaryExpr(){};
        OPCode op;
        std::shared_ptr<Expr> left;
        std::shared_ptr<Expr> right;
        llvm::Value* Accept(Visitor* visitor) override {
            return visitor->VisitorBinaryExpr(this);
        }

};

class FactorExpr: public Expr{
    public:
        ~FactorExpr(){};
        int number;
        llvm::Value* Accept(Visitor* visitor) override {
            return visitor->VisitorFactorExpr(this);
        }

};

class Program {
    public:
        ~Program(){};
        std::vector<std::shared_ptr<Expr>> exprVec;
        llvm::Value* Accept(Visitor* visitor) {
            return visitor->VisitorProgram(this);
        }
};