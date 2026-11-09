#ifndef VELOX_PARSER_H
#define VELOX_PARSER_H

#include "lexer.h"
#include <vector>
#include <cstddef>

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

private:
    const std::vector<Token>& tokens;
    std::size_t current;

    // Token navigation functions
    bool isAtEnd() const;
    const Token& peek() const;
    const Token& previous() const;
    const Token& advance();

    // Token checking functions
    bool check(TokenType type) const;
    bool match(TokenType type);
    const Token& expect(TokenType type, const std::string& message);
};

#endif