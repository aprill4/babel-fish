#pragma token_h
#include <string.h>

typedef enum {
    // Arithmetic operation: + - * / %
    TOKEN_ADD = 258,
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
    TOKEN_EOF,
    // Blank
    TOKEN_NEWLINE,
	TOKEN_WHITESPACE,
    // Comment
    TOKEN_COMMENT,
    // Other
    TOKEN_OTHER,
    // Val
    TOKEN_IDENTIFIER,
    TOKEN_INTEGER,
    TOKEN_FLOATPOINT,
} TokenType;

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
