#pragma token_h
enum TokenType{

    // imagine here is an ASCII table
    TOKEN_EOF = 0,
    // end of ASCII table

    TOKEN_IDENTIFIER = 128,
    TOKEN_INTEGER,
    TOKEN_FLOAT_POINT_NUMBER,

    TOKEN_NE,
    TOKEN_ET,
    TOKEN_LTE,
    TOKEN_GTE,
    TOKEN_LT,
    TOKEN_GT,

    TOKEN_KEYWORD_IF,
    TOKEN_KEYWORD_ELSE,

    TOKEN_KEYWORD_WHILE,

    TOKEN_KEYWORD_INT,
    TOKEN_KEYWORD_FLOAT,
    TOKEN_KEYWORD_RETURN,
    TOKEN_KEYWORD_CONTINUE,
    TOKEN_KEYWORD_BREAK,
    TOKEN_KEYWORD_VOID,
    TOKEN_KEYWORD_CONST,

    TOKEN_LOGICAL_AND,
    TOKEN_LOGICAL_OR
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