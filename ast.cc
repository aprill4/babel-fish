#include "ast.h"
#include "syntax_analyzer.tab.h"
Node::Node() : line(yylloc.first_line), column(yylloc.first_column) {}