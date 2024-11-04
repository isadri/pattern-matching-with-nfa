#include <State.hpp>
#include <Re2NFA.hpp>
#include <Parser.hpp>
#include <iostream>

State*  Re2NFA::start(const char* re) {
    return build(Parser::parse(re).get()).start;
}

Fragment    Re2NFA::build(Expr* expr) {
    expr->accept(*this);

    if (_fragments.size() != 1)
        throw std::runtime_error("error in nfa construction.");
    Fragment    frag{ _fragments.top() };

    _fragments.pop();
    patch(frag.out, State::create(Value::ACCEPT, nullptr, nullptr));
    return frag;
}

void    Re2NFA::visitAltExpr(const Alt& expr) {
    expr.left()->accept(*this);
    expr.right()->accept(*this);

    Fragment    f2{ pop() };
    Fragment    f1{ pop() };
    State*      state{ State::create(Value::SPLIT, f1.start, f2.start) };

    push(state, append(f1.out, f2.out));
}

void    Re2NFA::visitConcatExpr(const Concat& expr) {
    expr.left()->accept(*this);
    expr.right()->accept(*this);

    Fragment    f2{ pop() };
    Fragment    f1{ pop() };

    patch(f1.out, f2.start);
    push(f1.start, f2.out);
}

void    Re2NFA::visitReptExpr(const Rept& expr) {
    expr.expr()->accept(*this);

    Fragment    f{ nullptr, nullptr };
    State*      state{ nullptr };
    int         opt{ expr.opt() };

    switch (opt) {
        case '*':
            f = pop();
            state = State::create(Value::SPLIT, f.start, nullptr);
            patch(f.out, state);
            push(state, create_list(&state->out2));
            break;
        case '+':
            f = pop();
            state = State::create(SPLIT, f.start, nullptr);
            patch(f.out, state);
            push(f.start, create_list(&state->out2));
            break;
        case '?':
            f = pop();
            state = State::create(SPLIT, f.start, nullptr);
            push(state, append(f.out, create_list(&state->out2)));
            break;
        default:
            throw std::runtime_error(std::string("invalid operator '")
                                    + static_cast<char>(opt) + "'");
    }
}

void    Re2NFA::visitAtomExpr(const Atom& expr) {
    expr.expr()->accept(*this);
}

void    Re2NFA::visitSymbolExpr(const Symbol& expr) {
    State*  state = State::create(expr.get(), nullptr, nullptr);

    push(state, create_list(&state->out1));
}

PtrList*    Re2NFA::create_list(State** s) {
    PtrList*    p;

    p = (PtrList*)s;
    p->next = nullptr;
    return p;
}

Fragment&   Re2NFA::pop() {
    Fragment&    frag{ _fragments.top() };

    _fragments.pop();
    return frag;
}

void    Re2NFA::push(State* start, PtrList* out) {
    _fragments.push({start, out});
}

PtrList*    Re2NFA::append(PtrList* l1, PtrList* l2) {
    PtrList*    old{ l1 };

    while (l1->next)
        l1 = l1->next;
    l1->next = l2;
    return old;
}

void    Re2NFA::patch(PtrList* list, State* state) {
    PtrList*    next;

    while (list) {
        next = list->next;
        list->state = state;
        list = next;
    }
}
