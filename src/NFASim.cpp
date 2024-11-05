#include <NFASim.hpp>
#include <Re2NFA.hpp>
#include <Parser.hpp>
#include <algorithm>
#include <iostream>

StateStack                          NFASim::_old_states;
StateStack                          NFASim::_new_states;
std::unordered_map<State*, bool>    NFASim::_already_on;
std::set<State*>                    NFASim::_states;

bool    NFASim::run(const char* re, const char* text) {
    Re2NFA  nfa;
    State*  start{ nfa.start(re) };

    reset();
    add_state(start);
    swap_states();
    for (const char* p = text; *p; ++p) {
        next_set(*p);
    }
    fill_set();
    return std::any_of(_states.begin(), _states.end(),
                    [](State* s) { return s->c == ACCEPT; });
}

void    NFASim::next_set(int c) {
    State*  state{ nullptr };

    while (!_old_states.empty()) {
        state = pop(_old_states);
        add_state(move(state, c));
    }
    swap_states();
}

void    NFASim::add_state(State* state) noexcept {
    if (!state || _already_on[state])
        return ;
    _new_states.push(state);
    _already_on[state] = true;
    if (state->c == SPLIT) {
        add_state(state->out1);
        add_state(state->out2);
    }
}

void    NFASim::swap_states() {
    State*  state{ nullptr };

    while (!_new_states.empty()) {
        state = pop(_new_states);
        _old_states.push(state);
        _already_on[state] = false;
    }
}

State*  NFASim::move(State* state, int c) noexcept {
    if (state->c == WIDLCARD)
        return state->out1;
    return state->c == c ? state->out1 : nullptr;
}

void    NFASim::fill_set() {
    while (!_old_states.empty())
        _states.insert(pop(_old_states));
}

State*  NFASim::pop(StateStack& states) {
    if (states.empty())
        throw std::logic_error("stack is empty.");
    State*  top{ states.top() };

    states.pop();
    return top;
}

void    NFASim::reset() noexcept {
    _old_states = StateStack();
    _new_states = StateStack();
    _states.clear();
    _already_on.clear();
}
