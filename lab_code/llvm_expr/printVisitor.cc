#include "printVisitor.h"

PrintVisitor::PrintVisitor(std::shared_ptr<Program> program) {
    VisitorProgram(program.get());
}

// llvm::Value* PrintVisitor::VisitorExpr(Expr *expr) {
//     return expr->Accept(this);
// }

llvm::Value* PrintVisitor::VisitorProgram(Program *program) {
    for (auto& expr : program->exprVec) {
        //这里注意类型分发
        expr->Accept(this);
        llvm::outs() << ";\n";
    }
    return nullptr;
}

llvm::Value* PrintVisitor::VisitorBinaryExpr(BinaryExpr *binaryExpr) {
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

    return nullptr;
}

llvm::Value* PrintVisitor::VisitorFactorExpr(FactorExpr *factorExpr) {
    llvm::outs() << factorExpr->number;
    return nullptr;
}
