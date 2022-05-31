#ifndef PARSER_H
#define PARSER_H
#include <vector>
enum Ast_Node_Type {
	Variable_Define,
	Variable_Call,
	Procedure_Define,
	Procedure_Call,
	AST_If,
	AST_While,
	AST_Return,
	ASt_Array_Define,
	AST_Array_Call,
	AST_Break,
	AST_Continue,
	AST_Assignment,
	AST_Imm,
	AST_Operator,
	AST_Block
};
enum operator_type {
	AST_MUL,
	AST_ADD,
	AST_DIV,
	AST_SUB,
	AST_LESS_THAN,
	AST_LESS_EQUAL_THAN,
	AST_GREATER_THAN,
	AST_GREATER_EQUAL_THAN,
	AST_EQUAL,
	AST_NOT_EQUAL
};
struct Ast_Node {
	Ast_Node_Type type;
	Ast_Node* next_node = 0;
	int line;

	Ast_Node(Ast_Node_Type t) {
		type = t;
	}
};
enum Variable_Type {
	INTEGER,
	FLOAT,
	VOID
};
struct Variable_Declaration :Ast_Node {
	Variable_Type variable_type;
	Ast_Node* value = 0;
	char* name;
	Variable_Declaration() :Ast_Node(Variable_Define) {}
};
struct Variable_Reference :Ast_Node {
	const char* name;
	Variable_Reference() :Ast_Node(Variable_Call) {}
};
struct Function_Realm :Ast_Node {
	Ast_Node* start = 0;
	Ast_Node* end = 0;
	vector<Ast_Node*> temp_variable;
	Function_Realm() :Ast_Node(AST_Block) {}
};
struct Procedure_Declaration :Ast_Node {
	Function_Realm* body = 0;
	Function_Realm* parent = 0;
	Variable_Type return_type;
	vector<Ast_Node*> params;
	const char* name;
	Procedure_Declaration() :Ast_Node(Procedure_Define) {}
};
struct Procedure_Reference :Ast_Node {
	const char* name = 0;
	Procedure_Reference() :Ast_Node(Procedure_Call) {}
};
struct Ast_If :Ast_Node {
	Ast_Node* condition = 0;
	Function_Realm* true_block = 0;
	Function_Realm* false_block = 0;
	Ast_If() :Ast_Node(AST_If) {}
};
struct Ast_While :Ast_Node {
	Ast_Node* condition = 0;
	Function_Realm* body = 0;
	Ast_While() :Ast_Node(AST_While) {}
};
struct Ast_Return :Ast_Node {
	Ast_Node* value = 0;
	Ast_Return() :Ast_Node(AST_Return) {}
};
struct Ast_Array_Reference :Ast_Node {
	const char* name = 0;
	int offset = 0;
	Ast_Array_Reference() :Ast_Node(AST_Array_Call) {}
};
struct Ast_Array_Declaration :Ast_Node {
	const char* name = 0;
	int dimension = 0;
	vector<int> size_each_dimension;
	Ast_Array_Declaration() :Ast_Node(ASt_Array_Define) {}
};
struct Ast_Break :Ast_Node {
	Ast_Break() :Ast_Node(AST_Break) {}
};
struct Ast_Continue :Ast_Node {
	Ast_Continue() :Ast_Node(AST_Continue) {}
};
struct Ast_Assignment :Ast_Node {
	Ast_Assignment() :Ast_Node(AST_Assignment) {}
};
struct Ast_Imm :Ast_Node {
	uint64 number = 0;//TODO: distinguish between float and int
	Ast_Imm() :Ast_Node(AST_Imm) {};
};
struct Ast_Operator :Ast_Node {
	operator_type op;
	Ast_Operator() :Ast_Node(AST_Operator) {}
};
struct AST {
	vector<Ast_Node*> Global_variables;
	vector<Ast_Node*> Procedures;
};

#endif