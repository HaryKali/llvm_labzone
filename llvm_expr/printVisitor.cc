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
        virtual void VisitExpr(Expr *expr){};
        virtual void VisitBinaryExpr(BinaryExpr *binaryExpr) =0 ;
        virtual void VisitFactorExpr(FactorExpr *factorExpr) =0 ; 
        virtual void VisitProgram(Program *program) =0 ;
};





class Expr{
    public:
        virtual ~Expr(){};
        virtual void Accept(Visitor *visitor) = 0;
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

        void Accept(Visitor *visitor) override {
            visitor->VisitBinaryExpr(this);
        }

};

class FactorExpr: public Expr{
    public:
        int number;
        void accept(Visitor *visitor) override {
            visitor->VisitFactorExpr(this);
        }

};

class Program {
    public:
        ~Program(){};
        std::vector<std::shared_ptr<Expr>> exprs;

        void accept(Visitor *visitor) override {
            visitor->VisitProgram(this);
        }
};