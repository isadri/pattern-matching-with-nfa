#pragma once

#include "Re2NFA.hpp"
#include <array>
#include <set>
#include <unordered_map>

using   StateStack = std::stack<State*>;

class   NFASim {
public:
    NFASim() = delete;

    static bool run(const char* re, const char* text);

//private:
    static StateStack                           _old_states;
    static StateStack                           _new_states;
    static std::unordered_map<State*, bool>     _already_on;
    static std::set<State*>                     _states;

    static void             add_state(State* state) noexcept;
    static void             next_set(int c);
    static State*           move(State* state, int c) noexcept;
    static void             swap_states();
    static void             reset() noexcept;
    static State*           pop(StateStack& states);
    static void             fill_set();
};
