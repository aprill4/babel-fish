#include "Instructions/GetElementPtrInst.h"
#include "BasicBlock.h"
#include "Types/ArrayType.h"
#include "Types/PointerType.h"
#include "Types/Type.h"
#include "Util.h"
#include "Value.h"
#include <cassert>

GetElementPtrInst::GetElementPtrInst(Context &context, Value *ptr,
                                     std::vector<Value *> idxList,
                                     BasicBlock *insertedBlock,
                                     std::string name)
    : Instruction(
          context, PointerType::get(context, computeElementType(ptr, idxList)),
          InstId::Getelementptr, idxList.size() + 1, insertedBlock, name) {
  setOperand(ptr, 0);
  for (int i = 0; i < idxList.size(); i++) {
    setOperand(idxList[i], i + 1);
  }
  elementType_ = computeElementType(ptr, idxList);
  insertedBlock->addInstruction(this);
}

GetElementPtrInst *GetElementPtrInst::Create(Context &context, Value *ptr,
                                             std::vector<Value *> idxList,
                                             BasicBlock *insertedBlock,
                                             std::string name) {
  return new GetElementPtrInst(context, ptr, idxList, insertedBlock, name);
}

Type *GetElementPtrInst::computeElementType(Value *ptr,
                                            std::vector<Value *> idxList) {
  Type *elementType = ptr->getType()->getPtrElementType();
  assert("GetElementPtrInst ptr is wrong type" &&
         (elementType->isArrayType() || elementType->isIntegerType() ||
          elementType->isFloatType()));
  if (elementType->isArrayType()) {
    ArrayType *arr_ty = static_cast<ArrayType *>(elementType);
    for (int i = 0; i < idxList.size(); i++) {
      elementType = arr_ty->getElementType();
      if (elementType->isArrayType()) {
        arr_ty = static_cast<ArrayType *>(elementType);
      }
    }
  }
  return elementType;
}

Type *GetElementPtrInst::getElementType() { return elementType_; }

std::string GetElementPtrInst::print() {
  std::string IR;
  char IRtemp[100];
  // <result> = getelementptr <type>, <type>* <ptrval> [, <type> <idx>]
  std::string fmt("%%%s = getelementptr %s, ");
  assert(getOperandType(0)->isPointerType());
  std::snprintf(IRtemp, sizeof IRtemp, fmt.c_str(), getLLVM_Name().c_str(),
                getOperandType(0)->getPtrElementType()->getTypeName().c_str());
  IR.assign(IRtemp);
  for (int i = 0; i < getOperandNum(); i++) {
    if (i > 0)
      IR += ", ";
    IR += getOperand(i)->getType()->getTypeName() + " " +
          print_as_op(getOperand(i));
  }
  return IR;
}
