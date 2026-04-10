#pragma once
#include <memory>
#include<vector>
class Expr{
    public:
        ~Expr(){};
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

};

class FactorExpr: public Expr{
    public:
        ~FactorExpr(){};
        int number;
};

class Program {
    public:
        ~Program(){};
        std::vector<std::shared_ptr<Expr>> exprs;
};