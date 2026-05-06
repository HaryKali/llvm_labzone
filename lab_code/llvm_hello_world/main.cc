#include <iostream>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Verifier.h>
// llvm Hello World
//  source-> ir -> run ir ->output "Hello world"
//.ll is the ir file of llvm
//.ll include moudule -> (global, function)
//  function ->(basic block )* at least we got one

// target :gen ->moudule->main function -> "hello world"
using namespace llvm;

//; ModuleID = 'Hello LLVM'
//@gStr = private constant [13 x i8]
// declare i32 @main()
// define i32 @main() {
// entry:
//   %call_puts = call i32 @puts(ptr @gStr)
//   ret i32 1
// }
int main()
{
    // cpp output
    //  std::cout<<"Hello World"<<std::endl;
    //  return 1;
    LLVMContext context;
    Module m("Hello LLVM", context);
    IRBuilder<> irBuilder(context);

    // int puts(cahr *str);
    FunctionType *putsFuncType = FunctionType::get(irBuilder.getInt32Ty(),
                                                   {irBuilder.getInt8PtrTy()}, false);

    Function *putsFunc = Function::Create(putsFuncType, GlobalValue::LinkageTypes::ExternalLinkage,
                                          "puts", m);

    llvm::Constant *c = ConstantDataArray::getString(context, "Hello,World\n");

    GlobalVariable *gvar = new GlobalVariable(m, c->getType(), true, GlobalValue::LinkageTypes::PrivateLinkage,
                                              c, "gStr");

    FunctionType *mainFuncType = FunctionType::get(irBuilder.getInt32Ty(), false);
    Function *mainFunc = Function::Create(mainFuncType, GlobalVariable::LinkageTypes::ExternalLinkage,
                                          "main", m);

    BasicBlock *entryBB = BasicBlock::Create(context, "entry", mainFunc);

    irBuilder.SetInsertPoint(entryBB);
    
    llvm::Value *gep = irBuilder.CreateGEP(gvar->getValueType(), gvar, {irBuilder.getInt64(0), irBuilder.getInt64(0)});
    
    irBuilder.CreateCall(putsFunc, {gep}, "call_puts");
    irBuilder.CreateRet(irBuilder.getInt32(1));
    
    verifyFunction(*mainFunc,&errs());
    
    verifyModule(m,&errs());

    m.print(outs(), nullptr);
    return 1;
}

//test_path:../../llvm17_labzone/build/bin/lli ./hello_world.ll