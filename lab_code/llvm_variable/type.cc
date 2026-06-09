#include "type.h"

CType *CType::GetIntType()
{
    static CType intType(TypeKind::Int, 4, 4);
    return &intType;
}