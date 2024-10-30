#pragma once

#include "Expr.hpp"

class   Visitor {
public:
    virtual ~Visitor() = default;

    virtual void visitAltExpr(const Alt& expr) = 0;
    virtual void visitConcatExpr(const Concat& expr) = 0;
    virtual void visitReptExpr(const Rept& expr) = 0;
    virtual void visitAtomExpr(const Atom& expr) = 0;
    virtual void visitSymbolExpr(const Symbol& expr) = 0;
};
