#pragma once
#include <memory>
#include<vector>
class Program;
class Expr;
class BinaryExpr;
class FactorExpr;
class Visitor{
    public:
        virtual ~Visitor(){};
        virtual void VisitorProgram(Program *p) = 0;
        virtual void VisitorExpr(Expr *expr) {};
        virtual void VisitorBinaryExpr(BinaryExpr *expr) = 0;
        virtual void VisitorFactorExpr(FactorExpr *expr) = 0;
};

class Expr{
    public:
        virtual ~Expr(){};
        virtual void Accept(Visitor* visitor) {};

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
        void Accept(Visitor* visitor) override {
            visitor->VisitorBinaryExpr(this);
        }

};

class FactorExpr: public Expr{
    public:
        ~FactorExpr(){};
        int number;
        void Accept(Visitor* visitor) override {
            visitor->VisitorFactorExpr(this);
        }

};

class Program {
    public:
        ~Program(){};
        std::vector<std::shared_ptr<Expr>> exprs;
        void Accept(Visitor* visitor) {
            visitor->VisitorProgram(this);
        }
};