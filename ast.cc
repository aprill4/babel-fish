#include "ast.h"
#include "parse.tab.h"
Node::Node() : line(yylloc.first_line), column(yylloc.first_column) {}