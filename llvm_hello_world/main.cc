#include<iostream>
#include<llvm/IR/Module.h>
#include<llvm/IR/IRBuilder.h>
#include<llvm/IR/LLVMContext.h>
//llvm Hello World
// source-> ir -> run ir ->output "Hello world"
//.ll is the ir file of llvm 
//.ll ->moudule -> (global, function)
// function ->(basic block )* at least we got one

//target ->gen ->moudule->main function -> "hello world" 

int main() {
    //cpp output
    std::cout<<"Hello World"<<std::endl;
    
    // Time to use ir to finish this

    return 1;
}