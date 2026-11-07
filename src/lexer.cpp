#include "lexer.h"

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
