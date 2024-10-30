#pragma once

#include <memory>

class   Visitor;

class   Expr {
public:
    virtual ~Expr() = 0;

    virtual void    accept(Visitor& visitor) = 0;
};

class   Alt: public Expr {
public:
    Alt(const std::shared_ptr<Expr>& left,
        const std::shared_ptr<Expr>& right);
    Alt(const Alt& alt);
    virtual ~Alt() = default;

    const std::shared_ptr<Expr>&    left() const noexcept;
    const std::shared_ptr<Expr>&    right() const noexcept;

    virtual void    accept(Visitor& visitor) override;

private:
    std::shared_ptr<Expr>   _left;
    std::shared_ptr<Expr>   _right;
};

class   Concat: public Alt {
public:
    Concat(const std::shared_ptr<Expr>& left,
            const std::shared_ptr<Expr>& right);
    Concat(const Concat& c);
    virtual ~Concat() = default;

    virtual void    accept(Visitor& visitor) override;
};

class   Rept: public Expr {
public:
    Rept(const std::shared_ptr<Expr>& expr, int opt);
    Rept(const Rept& r);
    virtual ~Rept() = default;

    const std::shared_ptr<Expr>&    expr() const noexcept;
    int                             opt() const noexcept;

    void    set_operator(int opt);
    virtual void    accept(Visitor& visitor) override;

private:
    std::shared_ptr<Expr>   _expr;
    int                     _opt;
};

class   Atom: public Expr {
public:
    Atom(const std::shared_ptr<Expr>& expr);
    Atom(const Atom& p);
    virtual ~Atom() = default;

    const std::shared_ptr<Expr>& expr() const noexcept;

    virtual void    accept(Visitor& visitor) override;

private:
    std::shared_ptr<Expr>   _expr;
};

class   Symbol: public Expr {
public:
    Symbol(int s);
    Symbol(const Symbol& symbol);
    virtual ~Symbol() = default;

    int get() const noexcept;
    
    virtual void    accept(Visitor& visitor) override;

private:
    int _symbol;
};
