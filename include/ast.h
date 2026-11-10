#ifndef VELOX_AST_H
#define VELOX_AST_H

#include <string>
#include <vector>
#include <memory>

struct Expr {
    virtual ~Expr() = default; // 
};

struct IntegerExpr : Expr {
    int value;

    explicit IntegerExpr(int value)
        : value(value) {}
};

struct VariableExpr : Expr {
    std::string name;

    explicit VariableExpr(const std::string& name)
        : name(name) {}
};

#endif
