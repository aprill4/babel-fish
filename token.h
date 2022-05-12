#pragma token_h
enum class TokenType{
    // + - * /
    ADD,
    SUB,
    MUL,
    DIV,
    // = < <= > >= == !=
    ASSIGN,
    LT,
    LTE,
    GT,
    GTE,
    EQ,
    NT,
    // ; , ( ) [ ] { }
    SEMI,
    COMMA,
    LP,
    RP,
    LB,
    RB,
    LBRACE,
    RBRACE,
    // int float void
    INT,
    FLOAT,
    VOID,

};

typedef struct {
    char text[128];
    int token;
    int line;
    int pos_start;
    int pos_end;
} Token;