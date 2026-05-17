#include "codegen.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/Value.h"
using namespace llvm;
llvm::Value* CodeGen::VisitorBinaryExpr(BinaryExpr *binaryExpr)
{
    llvm::Value *left = binaryExpr->left->Accept(this);
    llvm::Value *right = binaryExpr->right->Accept(this);
    switch (binaryExpr->op) {
        case OPCode::ADD:{
            return IRbuilder.CreateNSWAdd(left, right, "addtmp");
        }
        case OPCode::SUB:{
            return IRbuilder.CreateNSWSub(left, right, "subtmp");
        }
        case OPCode::MUL:{
            return IRbuilder.CreateNSWMul(left, right, "multmp");
        }
        case OPCode::DIV:{
            return IRbuilder.CreateSDiv(left, right, "divtmp");
        }
        default: 
            break;
    }
    return nullptr;
}
llvm::Value* CodeGen::VisitorFactorExpr(FactorExpr *factorExpr)
{
    return IRbuilder.getInt32(factorExpr->number);
}
// llvm::Value* CodeGen::VisitorExpr(Expr *expr)
// {
//     return expr->Accept(this);
// }

llvm::Value* CodeGen::VisitorProgram(Program *program)
{
    //main 
   auto mFuncType = FunctionType::get(IRbuilder.getInt32Ty(), false);
   auto mFunc=   Function::Create(mFuncType, GlobalValue::ExternalLinkage, "main", module.get());
    BasicBlock *entryBB = BasicBlock::Create(context, "entry", mFunc);
    for(auto &expr: program->exprVec){
        expr->Accept(this);
    }
    
    llvm::Value* ret = IRbuilder.CreateRet(IRbuilder.getInt32(0));

    
    IRbuilder.SetInsertPoint(entryBB);
    IRbuilder.CreateRet(IRbuilder.getInt32(0));
    
    verifyFunction(*mFunc);

    module->print(outs(), nullptr);
    return nullptr;
}
