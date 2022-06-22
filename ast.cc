#include "ast.h"
#include "syntax_analyzer.tab.h"
Node::Node() : line_(yylloc.first_line), column_(yylloc.first_column) {}