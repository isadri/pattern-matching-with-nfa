#include <Expr.hpp>
#include <Visitor.hpp>

Expr::~Expr() = default;

// Alternate
Alt::Alt(const std::shared_ptr<Expr>& left,
        const std::shared_ptr<Expr>& right)
    : _left(left)
    , _right(right)
{}

Alt::Alt(const Alt& alt) : _left(alt._left), _right(alt._right) {}

const std::shared_ptr<Expr>&    Alt::left() const noexcept {
    return _left;
}

const std::shared_ptr<Expr>&    Alt::right() const noexcept {
    return _right;
}

void    Alt::accept(Visitor& visitor) {
    visitor.visitAltExpr(*this);
}

// Concatente
Concat::Concat(const std::shared_ptr<Expr>& left,
            const std::shared_ptr<Expr>& right)
    : Alt(left, right)
{}

Concat::Concat(const Concat& c) : Alt(c) {}

void    Concat::accept(Visitor& visitor) {
    visitor.visitConcatExpr(*this);
}

// Reputation
Rept::Rept(const std::shared_ptr<Expr>& expr, int opt) : _expr(expr), _opt(opt)
{}

Rept::Rept(const Rept& r) : _expr(r._expr), _opt(r._opt) {}

const std::shared_ptr<Expr>&    Rept::expr() const noexcept {
    return _expr;
}

int Rept::opt() const noexcept {
    return _opt;
}

void    Rept::accept(Visitor& visitor) {
    visitor.visitReptExpr(*this);
}

//void    Rept::set_expr(const std::shared_ptr<Expr>& expr) {
//    _expr = expr;
//}

void    Rept::set_operator(int opt) {
    _opt = opt;
}

// Atom
Atom::Atom(const std::shared_ptr<Expr>& expr) : _expr(expr) {}

Atom::Atom(const Atom& p) : _expr(p._expr) {}

const std::shared_ptr<Expr>&    Atom::expr() const noexcept {
    return _expr;
}

void    Atom::accept(Visitor& visitor) {
    visitor.visitAtomExpr(*this);
}

// Symbol
Symbol::Symbol(int s) : _symbol(s) {}

Symbol::Symbol(const Symbol& symbol) : _symbol(symbol._symbol) {}

int Symbol::get() const noexcept {
    return _symbol;
}

void    Symbol::accept(Visitor& visitor) {
    visitor.visitSymbolExpr(*this);
}
