#include "../include/Type.h"

Type::Type(TypeId typdId) : typeId_(typdId) {}

std::string Type::getTypeName() {
  std::string typeName;
//   switch (typeId_) {
//   case TypeId::VoidTypeId:
//     typeName += "void";
//     break;
//   case TypeId::LabelTypeId:
//     typeName += "label";
//     break;
//   case TypeId::IntegerTypeId:
//     typeName += "i";
//     typeName +=
//         std::to_string(static_cast<IntegerType *>(this)->get_num_bits());
//     break;
//   case TypeId::FunctionTypeId:
//     typeName += static_cast<FunctionType *>(this)->get_return_type()->print();
//     typeName += " (";
//     for (int i = 0; i < static_cast<FunctionType *>(this)->get_num_of_args();
//          i++) {
//       if (i)
//         typeName += ", ";
//       typeName += static_cast<FunctionType *>(this)->get_param_type(i)->print();
//     }
//     typeName += ")";
//     break;
//   case TypeId::PointerTypeId:
//     typeName += this->get_pointer_element_type()->print();
//     typeName += "*";
//     break;
//   case TypeId::ArrayTypeId:
//     typeName += "[";
//     typeName +=
//         std::to_string(static_cast<ArrayType *>(this)->get_num_of_elements());
//     typeName += " x ";
//     typeName += static_cast<ArrayType *>(this)->get_element_type()->print();
//     typeName += "]";
//     break;
//   case TypeId::FloatTypeId:
//     typeName += "float";
//     break;
//   default:
//     break;
//   }
  return typeName;
}