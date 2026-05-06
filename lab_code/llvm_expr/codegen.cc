#include "codegen.h"
#include "llvm/IR/Verifier.h"
using namespace llvm;
void CodeGen::VisitorBinaryExpr(BinaryExpr *binaryExpr)
{
    
}
void CodeGen::VisitorFactorExpr(FactorExpr *factorExpr)
{
}
void CodeGen::VisitorProgram(Program *program)
{
    //main 
   auto mFuncType = FunctionType::get(IRbuilder.getInt32Ty(), false);
   auto mFunc=   Function::Create(mFuncType, GlobalValue::ExternalLinkage, "main", module.get());
    BasicBlock *entryBB = BasicBlock::Create(context, "entry", mFunc);
    IRbuilder.SetInsertPoint(entryBB);
    IRbuilder.CreateRet(IRbuilder.getInt32(0));
    
    verifyFunction(*mFunc);

    module->print(outs(), nullptr);

}
