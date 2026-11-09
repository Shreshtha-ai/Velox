#include "parser.h"
#include <stdexcept>
#include <string>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), current(0) {
}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::END_OF_FILE;
}

const Token& Parser::peek() const {
    return tokens[current];
}
const Token& Parser::previous() const {
    return tokens[current - 1];
}

const Token& Parser::advance() {
    if (!isAtEnd()) {
        current++;
    }

    return previous();
}

bool Parser::check(TokenType type) const { // it just checks if the current token matches the expected type without consuming it
    if (isAtEnd()) {
        return false;
    }

    return peek().type == type;
}

bool Parser::match(TokenType type) { //combines checking and consuming a token if it matches the expected type
    if (check(type)) {
        advance();
        return true;
    }

    return false;
}

const Token& Parser::expect(
    TokenType type,
    const std::string& message
) {
    if (check(type)) {
        return advance();
    }

    throw std::runtime_error(
        message + " at line " +
        std::to_string(peek().line) +
        ", column " +
        std::to_string(peek().column)
    );
}