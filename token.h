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
    TOKEN_BLANK,
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
    Token(TokenType _type,int _line,int _pos_start,int _pos_end):type(_type),line(_line),pos_start(_pos_start),pos_end(_pos_end){
    }
    Token(const Token& token):Token(token.type,token.line,token.pos_start,token.pos_end){
        this->data = token.data;
    }
    Token(TokenType _type,int _line,int _pos_start,int _pos_end,int _int_val):Token(_type,_line,_pos_start,_pos_end){
        data.int_val = _int_val;
    }
    Token(TokenType _type,int _line,int _pos_start,int _pos_end,float _float_val):Token(_type,_line,_pos_start,_pos_end){
        data.float_val = _float_val;
    }    
    Token(TokenType _type,int _line,int _pos_start,int _pos_end,const char* _identifier):Token(_type,_line,_pos_start,_pos_end){
        data.identifier = new char[strlen(_identifier)];
        strcpy(data.identifier, _identifier);
    }
    ~Token() = default;
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