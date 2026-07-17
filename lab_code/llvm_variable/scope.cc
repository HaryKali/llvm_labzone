#include "scope.h"

Scope::Scope()
{
    envs.push_back(std::make_shared<Env>()); //global
}
void Scope::EnterScope()
{
}
void Scope::ExitScope()
{
}
std::shared_ptr<Symbol> Scope::FindSymbol(llvm::StringRef name)
{
}
std::shared_ptr<Symbol> Scope::FindSymbolInCurrentScope(llvm::StringRef name)
{
}
void Scope::AddSymbol(SymbolKind kind, CType *ty, llvm::StringRef name)
{
}
