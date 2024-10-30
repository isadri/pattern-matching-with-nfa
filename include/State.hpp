#pragma once

#include <memory>
#include <list>

enum Value {
    SPLIT = 256,
    ACCEPT = 257
};

struct  State {
public:
    State(int c, State* o1, State* o2);
    bool    operator==(const State&);

    static State*   create(int c, State* o1, State* o2);

    int     c;
    State*  out1;
    State*  out2;
};

using   PtrList = union PtrList {
    State*      state;
    PtrList*    next;
};

struct  Fragment {
    Fragment(State* s, PtrList* o);

    State*      start;
    PtrList*    out;
};
