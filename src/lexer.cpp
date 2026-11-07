#include "lexer.h"
#include <cctype> // it provides fxn such as isalnum isalpha 

Lexer::Lexer(const std::string& source)
    : source(source), position(0), line(1), column(1) {
}



bool Lexer::isAtEnd() const {
    return position >= source.size();
}
char Lexer::peek() const {
    if (isAtEnd()) {
        return '\0';
    }

    return source[position];
}

char Lexer::peekNext() const {
    if (position + 1 >= source.size()) {
        return '\0';
    }

    return source[position + 1];
}


char Lexer::advance() {
    if (isAtEnd()) {
        return '\0';
    }

    char current = source[position];
    position++;

    if (current == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }

    return current;
}

bool Lexer::match(char expected) {
    if (isAtEnd()) {
        return false;
    }

    if (peek() != expected) {
        return false;
    }

    advance();
    return true;
}


Token Lexer::makeToken( //aggregate initialization
    TokenType type,
    std::size_t start,
    int startLine,
    int startColumn
) {
    std::string lexeme = source.substr(start, position - start);

    return Token{
        type,
        lexeme,
        startLine,
        startColumn
    };
}


Token Lexer::readIdentifierOrKeyword() {

    std::size_t start = position;
    int startLine = line;
    int startColumn = column;

    // Read the complete word
    while (!isAtEnd() &&
           (std::isalnum(static_cast<unsigned char>(peek())) ||
            peek() == '_')) {

        advance();
    }

    // Extract the complete word
    std::string text = source.substr(start, position - start);

    // Initially assume it is an identifier
    TokenType type = TokenType::IDENTIFIER;

    // Check whether it is a reserved keyword
    if (text == "int") {
        type = TokenType::KW_INT;
    }
    else if (text == "return") {
        type = TokenType::KW_RETURN;
    }
    else if (text == "void") {
        type = TokenType::KW_VOID;
    }
    else if (text == "char") {
        type = TokenType::KW_CHAR;
    }
    else if (text == "if") {
        type = TokenType::KW_IF;
    }
    else if (text == "else") {
        type = TokenType::KW_ELSE;
    }
    else if (text == "while") {
        type = TokenType::KW_WHILE;
    }

    // Create and return the token
    return makeToken(type, start, startLine, startColumn);
}


Token Lexer::readNumber(){

    std::size_t start = position;
    int startline = line;
    int startcolumn = column;

    while(!isAtEnd() && std::isdigit(static_cast<unsigned char>(peek()))){
        advance();
    }


    return makeToken(TokenType::INTEGER_LITERAL, start, startline, startcolumn);
    
}
