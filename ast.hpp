#ifndef AST_HPP
#define AST_HPP
#include <vector>
#include <string>
#include <memory>
using namespace std;
enum SysType {
    INT,
    FLOAT,
    VOID
};

enum BinaryOp {
    LE,
    LT,
    GE,
    GT,
    EQ,
    NEQ,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    AND,
    OR
};

enum UnaryOp{
    POSITIVE,
    NEGATIVE,
    NOT
};

struct ASTNode;
struct ASTCompUnit;
struct ASTDef;
struct ASTVarDef; 
struct ASTInitVal;
struct ASTDecl;
struct ASTExp;
struct ASTNum;
struct ASTUnaryExp;
struct ASTPrimaryExp;
struct ASTBinaryExp;
struct ASTParam;
struct ASTFuncDef;
struct ASTBlock;
struct ASTBlockItem;
struct ASTStatement;
struct ASTSelectionStmt;
struct ASTIterationStmt;
struct ASTBreakStmt;
struct ASTContinueStmt;
struct ASTReturnStmt;
struct ASTAssignExp;
struct ASTLval;
struct ASTCall;
struct ASTUnaryOpExp;

struct ASTNode {

};

struct ASTCompUnit: ASTNode {
    vector<shared_ptr<ASTDecl> > declarations;
    vector<shared_ptr<ASTFuncDef> > func_defs;
};

struct ASTDef: ASTNode {
    SysType type;
    string id;
};

struct ASTVarDef: ASTDef {
    bool is_const; //false if variable ,true if const
    vector<unsigned>dimensions; //empty if element is not an array
};

struct ASTInitVal: ASTNode {
    vector<unsigned>dimensions; //empty if element is not an array
    vector<shared_ptr<ASTExp> > elements;
};

struct ASTExp: ASTNode {
    
};

struct ASTUnaryExp: ASTExp {

};

struct ASTBinaryExp: ASTExp {
    shared_ptr<ASTExp> first;
    BinaryOp op;
    shared_ptr<ASTExp> second;
};

struct ASTParam: ASTDef {
    vector<shared_ptr<ASTExp>> dimensions; //0 is reserved for the empty dimension,e.g. []
};

struct ASTFuncDef: ASTDef {
    vector<shared_ptr<ASTParam> > params;
    shared_ptr<ASTBlock> block;
};

struct ASTBlockItem: ASTNode {
    
};

struct ASTDecl: ASTBlockItem {
    vector<pair<shared_ptr<ASTVarDef>,shared_ptr<ASTInitVal> >> definitions;
};

struct ASTStatement: ASTBlockItem {
    
};

struct ASTBlock: ASTStatement {
    vector<shared_ptr<ASTBlockItem>> block_items;
};

struct ASTSelectionStmt: ASTStatement {
    shared_ptr<ASTBinaryExp>cond;
    shared_ptr<ASTStatement> if_statement;
    // should be nullptr if no else structure exists
    shared_ptr<ASTStatement> else_statement;
};

struct ASTIterationStmt: ASTStatement {
    shared_ptr<ASTBinaryExp> cond;
    shared_ptr<ASTStatement> statement;
};

struct ASTBreakStmt: ASTStatement {

};

struct ASTContinueStmt: ASTStatement {

};

struct ASTReturnStmt: ASTStatement {
    // should be nullptr if return void
    shared_ptr<ASTExp> expression; 
};

struct ASTAssignExp: ASTStatement {
    shared_ptr<ASTLval> lval;
    shared_ptr<ASTExp> exp;
};

struct ASTCall: ASTUnaryExp {
    string id;
    vector<shared_ptr<ASTExp> > args;
};

struct ASTUnaryOpExp: ASTUnaryExp {
    UnaryOp op;
    shared_ptr<ASTUnaryExp> unary_exp;
};

struct ASTPrimaryExp: ASTUnaryExp {

};

struct ASTLval: ASTPrimaryExp {
    string id;
    vector<shared_ptr<ASTExp>> dimensions;
};

struct ASTNum: ASTPrimaryExp {
    SysType type;
    union {
        int i_val;
        float f_val;
    };
};


#endif