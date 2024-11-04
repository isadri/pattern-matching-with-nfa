#pragma once

#include "Visitor.hpp"
#include "State.hpp"
#include <stack>

class   Re2NFA: public Visitor {
public:
    virtual ~Re2NFA() = default;

    State*  start(const char* re);

    virtual void visitAltExpr(const Alt& expr) override;
    virtual void visitConcatExpr(const Concat& expr) override;
    virtual void visitReptExpr(const Rept& expr) override;
    virtual void visitAtomExpr(const Atom& expr) override;
    virtual void visitSymbolExpr(const Symbol& expr) override;

//private:
    std::stack<Fragment>    _fragments;
    std::shared_ptr<State>  _b;

    PtrList*    create_list(State** s);
    Fragment&   pop();
    void        push(State* start, PtrList* out);
    PtrList*    append(PtrList* l1, PtrList* l2);
    void        patch(PtrList* list, State* state);

    Fragment    build(Expr* expr);
};
