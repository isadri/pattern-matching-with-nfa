#include "../include/State.hpp"

State::State(int c, State* o1, State* o2)
    : c(c)
    , out1(o1)
    , out2(o2)
{}

State*  State::create(int c, State* o1, State* o2) {
    return new State(c, o1, o2);
}

bool    State::operator==(const State& state) {
    return c == state.c && out1 == state.out1 && out2 == state.out2;
}

Fragment::Fragment(State* s, PtrList* o)
    : start(s)
    , out(o)
{}
