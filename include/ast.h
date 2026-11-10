#ifndef VELOX_AST_H
#define VELOX_AST_H
#include "lexer.h"
#include <string>
#include <vector>
#include <memory>


struct Expr {
    virtual ~Expr() = default;
};

// Integer literal: 10, 20, 100
struct IntegerExpr : Expr {
    int value;

    explicit IntegerExpr(int value)
        : value(value) {}
};

// Variable reference: age, marks
struct VariableExpr : Expr {
    std::string name;

    explicit VariableExpr(const std::string& name)
        : name(name) {}
};

// Binary expression: a + b, x * y
struct BinaryExpr : Expr {
    std::unique_ptr<Expr> left;
    TokenType op;
    std::unique_ptr<Expr> right;

    BinaryExpr(
        std::unique_ptr<Expr> left,
        TokenType op,
        std::unique_ptr<Expr> right
    )
        : left(std::move(left)),
          op(op),
          right(std::move(right)) {}
};


struct Stmt {
    virtual ~Stmt() = default;
};

// Return statement: return 10;
struct ReturnStmt : Stmt {
    std::unique_ptr<Expr> expression;

    explicit ReturnStmt(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}
};

struct VarDeclStmt : Stmt {
    std::string name;
    std::unique_ptr<Expr> initializer;

    VarDeclStmt(
        const std::string& name,
        std::unique_ptr<Expr> initializer
    )
        : name(name),
          initializer(std::move(initializer)) {}
};

struct BlockStmt : Stmt {
    std::vector<std::unique_ptr<Stmt>> statements;
};


struct FunctionDecl {
    std::string returnType;
    std::string name;
    std::unique_ptr<BlockStmt> body;
};


struct Program {
    std::vector<std::unique_ptr<FunctionDecl>> functions;
};

#endif