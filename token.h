#pragma token_h
enum TokenType{
    // Arithmetic operation: + - * / %
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_MOD,
    // Relational operation: == != < > <= >= =
    TOKEN_EQ,
    TOKEN_NEQ,
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_LTE,
    TOKEN_GTE,
    TOKEN_ASSIGN,
    // Logical operation: ! && ||
    TOKEN_NOT,
    TOKEN_AND,
    TOKEN_OR,
    // Keyword: if else while int float void const return continue break 
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_VOID,
    TOKEN_CONST,
    TOKEN_RETURN,
    TOKEN_CONTINUE,
    TOKEN_BREAK,
    // Keyword: ; , ( ) [ ] { }
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_LEFT_PARENTHESES,
    TOKEN_RIGHT_PARENTHESES,
    TOKEN_LEFT_BRACKETS,
    TOKEN_RIGHT_BRACKETS,
    TOKEN_LEFT_BRACES,
    TOKEN_RIGHT_BRACES,
    // End of line 
    TOKEN_EOF = 0,
    // Blank
    TOKEN_BLANK,
    // Comment
    TOKEN_COMMENT,
    // Other
    TOKEN_OTHER,
    // Val
    TOKEN_IDENTIFIER = 128,
    TOKEN_INTEGER,
    TOKEN_FLOATPOINT,
};

typedef struct {
    TokenType type;
    int line;
    int pos_start;
    int pos_end;
    union {
        int int_val;
        float float_val;
        char *identifier;
    } data;
} Token;