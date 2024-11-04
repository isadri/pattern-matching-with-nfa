#pragma once

#include <initializer_list>
#include "Expr.hpp"

class   Parser {
public:
    static std::shared_ptr<Expr>    parse(const char* re);

private:
    static const char*  _ptr;

    static std::shared_ptr<Expr>    regex();
    static std::shared_ptr<Expr>    alternation();
    static std::shared_ptr<Expr>    concatentation();
    static std::shared_ptr<Expr>    repetition();
    static std::shared_ptr<Expr>    atom();

    static bool match(const std::initializer_list<int>& opts) noexcept;
    static bool is_operator(int c) noexcept;
    static bool is_symbol() noexcept;
    static int  advance() noexcept;
    static bool check(const std::initializer_list<int>& opts);
    static bool non_metachar() noexcept;
    static void consume(int c);
    static int  peek() noexcept;
    static bool metachar() noexcept;

    static std::shared_ptr<Expr>    make_range_node(int first, int last);
    static std::shared_ptr<Expr>    make_word_node();
};
