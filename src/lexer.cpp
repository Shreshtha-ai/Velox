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
