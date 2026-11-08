#include "lexer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>

// Converts TokenType enum values into readable names for users 
std::string tokenTypeName(TokenType type) {
    switch (type) {
        case TokenType::KW_INT: return "KW_INT";
        case TokenType::KW_RETURN: return "KW_RETURN";
        case TokenType::KW_VOID: return "KW_VOID";
        case TokenType::KW_CHAR: return "KW_CHAR";
        case TokenType::KW_IF: return "KW_IF";
        case TokenType::KW_ELSE: return "KW_ELSE";
        case TokenType::KW_WHILE: return "KW_WHILE";

        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::INTEGER_LITERAL: return "INTEGER_LITERAL";

        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::STAR: return "STAR";
        case TokenType::SLASH: return "SLASH";
        case TokenType::PERCENT: return "PERCENT";

        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::NOT: return "NOT";
        case TokenType::NOT_EQUAL: return "NOT_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";

        case TokenType::LOGICAL_AND: return "LOGICAL_AND";
        case TokenType::LOGICAL_OR: return "LOGICAL_OR";

        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
        case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::COMMA: return "COMMA";

        case TokenType::END_OF_FILE: return "END_OF_FILE";
    }

    return "UNKNOWN";
}

int main(int argc, char* argv[]) { //argc = argument count, argv = argument vector (array of strings)

    // Check whether the user supplied a filename.
    if (argc < 2) {
        std::cerr << "Usage: velox <source-file>\n";
        return 1;
    }

    // Open the source file.
    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file: "
                  << argv[1] << '\n';
        return 1;
    }

    // Read the entire file into a string.
    std::stringstream buffer;
    buffer << inputFile.rdbuf();

    std::string sourceCode = buffer.str();

    try {
        // Create the lexer.
        Lexer lexer(sourceCode);

        // Convert source code into tokens.
        std::vector<Token> tokens = lexer.tokenize();

        // Print the tokens.
        std::cout << "Lexing successful!\n\n";

        for (const Token& token : tokens) {
            std::cout << tokenTypeName(token.type)
                      << "\t"
                      << "'" << token.lexeme << "'"
                      << "\tLine: " << token.line
                      << "\tColumn: " << token.column
                      << '\n';
        }
    }
    catch (const std::exception& error) {
        std::cerr << "Lexer error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}