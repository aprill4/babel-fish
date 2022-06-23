#include "ast.h"
#include "syntax_analyzer.tab.h"
Node::Node() : line_(yylloc.first_line), column_(yylloc.first_column) {}

void* find_symbol(Scope* scope, std::string symbol, bool is_var) {
    while(scope)
        if(is_var && scope->varDeclares_.count(symbol)) return scope->varDeclares_[symbol];
        else if(!is_var && scope->funcDeclares_.count(symbol)) return scope->funcDeclares_[symbol]; 
        else scope = scope->parent; 
    return nullptr;
}