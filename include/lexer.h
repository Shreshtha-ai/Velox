#ifndef VELOX_LEXER_H
#define VELOX_LEXER_H

#include <string>
#include<vector>
#include<cstddef> 

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



struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};


class Lexer {
    public:
        explicit Lexer(const std::string& source);
        std::vector<Token> tokenize();
    private:
        std::string source;
        std::size_t position;
        int line;
        int column;


        bool isAtEnd() const;
        char peek() const;
        char peekNext() const;
        char advance();
        bool match(char expected);

        Token makeToken(TokenType type,
                    std::size_t start,
                    int startLine,
                    int startColumn);


        Token readIdentifierOrKeyword();
        Token readNumber();
        Token readOperatorOrPunctuation();


        void skipWhitespaceAndComments();
};








#endif