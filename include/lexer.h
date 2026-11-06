#ifndef MYCC_LEXER_H
#define MYCC_LEXER_H

#include <string>

enum class TokenType{
        KW_INT,
        KW_RETURN,
        KW_VOID,
        KW_CHAR,
        KW_IF,
        KW_ELSE,
        KW_WHILE,
        KW_FOR,
        KW_BREAK,
        KW_CONTINUE,

        IDENTIFIER,
        INTEGER_LITERAL,
        PLUS,
        MINUS,
        STAR,
        SLASH,
        PERCENT,


        ASSIGN,
        EQUAL,
        NOT,
        NOT_EQUAL,
        LESS,
        LESS_EQUAL,
        GREATER,
        GREATER_EQUAL,
        LOGICAL_AND,
        LOGICAL_OR,

        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        SEMICOLON,
        COMMA,

        END_OF_FILE,





};

#endif 
