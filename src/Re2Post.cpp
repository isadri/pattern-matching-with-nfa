#include <Re2Post.hpp>

void    Re2Post::run(Expr* expr) {
    expr->accept(*this);
}

void    Re2Post::visitAltExpr(const Alt& expr) {
    expr.left()->accept(*this);
    expr.right()->accept(*this);
    _result += '|';
}

void    Re2Post::visitConcatExpr(const Concat& expr) {
    expr.left()->accept(*this);
    expr.right()->accept(*this);
    _result += '.';
}

void    Re2Post::visitReptExpr(const Rept& expr) {
    expr.expr()->accept(*this);
    _result += expr.opt();
}

void    Re2Post::visitAtomExpr(const Atom& expr) {
    expr.expr()->accept(*this);
}

void    Re2Post::visitSymbolExpr(const Symbol& expr) {
    int c{ expr.get() };
    
    if (c)
        _result += c;
}

std::string  Re2Post::result() noexcept {
    std::string cpy{ _result };

    _result.clear();
    return cpy;
}
