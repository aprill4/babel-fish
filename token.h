#pragma token_h
#include <string.h>

#define TOKEN_ITEMS(F) \
	F(START) \
    F(TOKEN_ADD) \
    F(TOKEN_SUB) \
    F(TOKEN_MUL) \
    F(TOKEN_DIV) \
    F(TOKEN_MOD) \
    F(TOKEN_EQ) \
    F(TOKEN_NEQ) \
    F(TOKEN_LT) \
    F(TOKEN_GT) \
    F(TOKEN_LTE) \
    F(TOKEN_GTE) \
    F(TOKEN_ASSIGN) \
    F(TOKEN_NOT) \
    F(TOKEN_AND) \
    F(TOKEN_OR) \
    F(TOKEN_IF) \
    F(TOKEN_ELSE) \
    F(TOKEN_WHILE) \
    F(TOKEN_INT) \
    F(TOKEN_FLOAT) \
    F(TOKEN_VOID) \
    F(TOKEN_CONST) \
    F(TOKEN_RETURN) \
    F(TOKEN_CONTINUE) \
    F(TOKEN_BREAK) \
    F(TOKEN_SEMICOLON) \
    F(TOKEN_COMMA) \
    F(TOKEN_LEFT_PARENTHESES) \
    F(TOKEN_RIGHT_PARENTHESES) \
    F(TOKEN_LEFT_BRACKETS) \
    F(TOKEN_RIGHT_BRACKETS) \
    F(TOKEN_LEFT_BRACES) \
    F(TOKEN_RIGHT_BRACES) \
    F(TOKEN_EOF) \
    F(TOKEN_IDENTIFIER) \
    F(TOKEN_INTEGER) \
    F(TOKEN_FLOATPOINT)
	
enum TokenType {
#define F(i) i,
	TOKEN_ITEMS(F)
#undef F
};

#define F(i) #i,
const char *lookup[] = {TOKEN_ITEMS(F)};
#undef F

typedef struct Token{
    Token() = default;
    Token(TokenType _type, int _line, int _col): type(_type), line(_line), col(_col){
    }
    Token(const Token& token): Token(token.type, token.line, token.col){
        this->data = token.data;
    }
    Token(TokenType _type, int _line, int _col, int _int_val): Token(_type, _line, _col){
        data.int_val = _int_val;
    }
    Token(TokenType _type, int _line, int _col, float _float_val): Token(_type, _line, _col){
        data.float_val = _float_val;
    }    
    Token(TokenType _type, int _line, int _col, const char* _identifier): Token(_type, _line, _col){
        data.identifier = new char[strlen(_identifier)];
        strcpy(data.identifier, _identifier);
    }

    ~Token() = default;
    TokenType type;
    int line;
    int col;
    //int pos_end;

    union {
        int int_val;
        float float_val;
        char *identifier;
    } data;

} Token;
