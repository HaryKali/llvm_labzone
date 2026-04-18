#include "printVisitor.h"

PrintVisitor::PrintVisitor(std::shared_ptr<Program> program) {
    VisitorProgram(program.get());
}

void PrintVisitor::VisitorProgram(Program *program) {
    for (auto& expr : program->exprs) {
        //这里注意类型分发
        expr->Accept(this);
        llvm::outs() << ";\n";
    }
}

void PrintVisitor::VisitorBinaryExpr(BinaryExpr *binaryExpr) {
    binaryExpr->left->Accept(this);
    binaryExpr->right->Accept(this);
    switch (binaryExpr->op) {
        case OPCode::ADD:
            llvm::outs() << " + ";
            break;
        case OPCode::SUB:
            llvm::outs() << " - ";
             break;
        case OPCode::MUL:
            llvm::outs() << " * ";
            break;
        case OPCode::DIV:
            llvm::outs() << " / ";
            break;
    }

}

void PrintVisitor::VisitorFactorExpr(FactorExpr *factorExpr) {
    llvm::outs() << factorExpr->number;
}
