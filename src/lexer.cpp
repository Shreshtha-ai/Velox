#include "lexer.h"
#include <cctype> // it provides fxn such as isalnum isalpha 
#include <stdexcept>

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


Token Lexer::readOperatorOrPunctuation() {

    std::size_t start = position;
    int startLine = line;
    int startColumn = column;

    // Consume the first character
    char current = advance();

    switch (current) {

        // Arithmetic operators
        case '+':
            return makeToken(TokenType::PLUS, start, startLine, startColumn);

        case '-':
            return makeToken(TokenType::MINUS, start, startLine, startColumn);

        case '*':
            return makeToken(TokenType::STAR, start, startLine, startColumn);

        case '/':
            return makeToken(TokenType::SLASH, start, startLine, startColumn);

        case '%':
            return makeToken(TokenType::PERCENT, start, startLine, startColumn);


        // Assignment and equality
        case '=':
            if (match('=')) {
                return makeToken(TokenType::EQUAL, start, startLine, startColumn);
            }
            return makeToken(TokenType::ASSIGN, start, startLine, startColumn);


        // NOT and NOT_EQUAL
        case '!':
            if (match('=')) {
                return makeToken(TokenType::NOT_EQUAL, start, startLine, startColumn);
            }
            return makeToken(TokenType::NOT, start, startLine, startColumn);


        // Less than and less than or equal
        case '<':
            if (match('=')) {
                return makeToken(TokenType::LESS_EQUAL, start, startLine, startColumn);
            }
            return makeToken(TokenType::LESS, start, startLine, startColumn);


        // Greater than and greater than or equal
        case '>':
            if (match('=')) {
                return makeToken(TokenType::GREATER_EQUAL, start, startLine, startColumn);
            }
            return makeToken(TokenType::GREATER, start, startLine, startColumn);


        // Logical AND
        case '&':
            if (match('&')) {
                return makeToken(TokenType::LOGICAL_AND, start, startLine, startColumn);
            }
            throw std::runtime_error("Unexpected '&'. Did you mean '&&'?");


        // Logical OR
        case '|':
            if (match('|')) {
                return makeToken(TokenType::LOGICAL_OR, start, startLine, startColumn);
            }
            throw std::runtime_error("Unexpected '|'. Did you mean '||'?");


        // Parentheses
        case '(':
            return makeToken(TokenType::LEFT_PAREN, start, startLine, startColumn);

        case ')':
            return makeToken(TokenType::RIGHT_PAREN, start, startLine, startColumn);


        // Braces
        case '{':
            return makeToken(TokenType::LEFT_BRACE, start, startLine, startColumn);

        case '}':
            return makeToken(TokenType::RIGHT_BRACE, start, startLine, startColumn);


        // Brackets
        case '[':
            return makeToken(TokenType::LEFT_BRACKET, start, startLine, startColumn);

        case ']':
            return makeToken(TokenType::RIGHT_BRACKET, start, startLine, startColumn);


        // Punctuation
        case ';':
            return makeToken(TokenType::SEMICOLON, start, startLine, startColumn);

        case ',':
            return makeToken(TokenType::COMMA, start, startLine, startColumn);


        // Unsupported character
        default:
            throw std::runtime_error(
                std::string("Unexpected character: '") + current + "'"
            );
    }
}


//whitespaces - spaces, tabs, newlines, and comments (single-line and multi-line) are ignored by the lexer.

void Lexer::skipWhitespaceAndComments(){
    while(!isAtEnd()){
        // Case 1: Skip whitespace
        if (std::isspace(static_cast<unsigned char>(peek()))) {
            advance();
        }

        // Case 2: Single-line comment //
        else if (peek() == '/' && peekNext() == '/') {

            // Consume both slashes
            advance();
            advance();

            // Skip until newline or end of file
            while (!isAtEnd() && peek() != '\n') {
                advance();
            }
        }

        // Case 3: Multiline comment /*
        else if (peek() == '/' && peekNext() == '*') {

            // Consume /*
            advance();
            advance();

            // Skip until */
            bool commentClosed = false;

            while (!isAtEnd()) {

                if (peek() == '*' && peekNext() == '/') {
                    advance();
                    advance();

                    commentClosed = true;
                    break;
                }

                advance();
            }

            if (!commentClosed) {
                throw std::runtime_error(
                    "Unterminated multiline comment"
                );
            }
        }

        // No whitespace or comment found
        else {
            break;
        }
    }
}   


   

