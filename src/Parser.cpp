#include <Parser.hpp>
#include <iostream>
#include <algorithm>

const char*   Parser::_ptr{ nullptr };

std::shared_ptr<Expr>   Parser::parse(const char* re) {
    if (!*re)
        throw std::runtime_error("bad regexp.");
    _ptr = re;
    std::shared_ptr<Expr>   expr{ regex() };

    if (*_ptr)
        throw std::runtime_error(std::string("Invalid character '")
                                + *_ptr + "'");
    return expr;
}

std::shared_ptr<Expr>   Parser::regex() {
    return alternation();
}

std::shared_ptr<Expr>   Parser::alternation() {
    std::shared_ptr<Expr>   expr{ concatentation() };

    while (match({'|'})) {
        if (!*_ptr)
            throw std::runtime_error("bad regexp.");
        std::shared_ptr<Expr>   right{ concatentation() };
        expr = std::make_shared<Alt>(expr, right);
    }
    return expr;
}

std::shared_ptr<Expr>   Parser::concatentation() {
    std::shared_ptr<Expr>   expr{ repetition() };

    while (*_ptr && *_ptr != '|' && *_ptr != ')') {
        std::shared_ptr<Expr>   right{ repetition() };
        expr = std::make_shared<Concat>(expr, right);
    }
    return expr;
}

std::shared_ptr<Expr>   Parser::repetition() {
    std::shared_ptr<Expr>   expr{ atom() };

    if (match({'*', '+', '?'}))
        expr = std::make_shared<Rept>(expr, *(_ptr - 1));
    return expr;
}

std::shared_ptr<Expr>   Parser::atom() {
    if (match({'('})) {
        std::shared_ptr<Expr>   expr{ regex() };
        consume(')');
        return std::make_shared<Atom>(expr);
    }
    if (match({'\\'})) {
        if (match({'d'}))
            return make_range_node('0', '9');
        if (match({'w'}))
            return make_word_node();
        return std::make_shared<Symbol>(advance());
    }
    if (non_metachar())
        return std::make_shared<Symbol>(advance());
    throw std::runtime_error("bad regexp.");
}

std::shared_ptr<Expr>   Parser::make_word_node() {
    std::shared_ptr<Expr>   expr{ std::make_shared<Symbol>('a') };
    std::shared_ptr<Expr>   right{ nullptr };

    for (int i = 'b'; i <= 'z'; ++i) {
        right = std::make_shared<Symbol>(i);
        expr = std::make_shared<Alt>(expr, right);
    }
    for (int i = 'A'; i <= 'Z'; ++i) {
        right = std::make_shared<Symbol>(i);
        expr = std::make_shared<Alt>(expr, right);
    }
    for (int i = '0'; i <= '9'; ++i) {
        right = std::make_shared<Symbol>(i);
        expr = std::make_shared<Alt>(expr, right);
    }
    return std::make_shared<Alt>(expr, std::make_shared<Symbol>('_'));
}

std::shared_ptr<Expr>   Parser::make_range_node(int first, int last) {
    std::shared_ptr<Expr>   expr{ std::make_shared<Symbol>(first) };
    std::shared_ptr<Expr>   right{ nullptr };

    for (int i = first + 1; i <= last; ++i) {
        right = std::make_shared<Symbol>(i);
        expr = std::make_shared<Alt>(expr, right);
    }
    return expr;
}

void    Parser::consume(int c) {
    if (!match({c}))
        throw std::runtime_error("bad regexp.");
}

bool    Parser::match(const std::initializer_list<int>& opts) noexcept {
    if (!*_ptr)
        return false;
    for (auto opt : opts) {
        if (opt == *_ptr) {
            advance();
            return true;
        }
    }
    return false;
}

int    Parser::advance() noexcept {
    return *_ptr ? *_ptr++ : '\0';
}

bool    Parser::check(const std::initializer_list<int>& opts) {
    return std::any_of(opts.begin(), opts.end(), [](int i) {
            return i == *_ptr;
        });
}

bool    Parser::is_symbol() noexcept {
    return !is_operator(*_ptr) && *_ptr != '(' && *_ptr != ')';
}

bool    Parser::is_operator(int c) noexcept {
    return c == '*' || c == '+' || c == '?' || c == '|';
}

bool    Parser::non_metachar() noexcept {
    return !metachar();
}

bool    Parser::metachar() noexcept {
    return check({'(', ')', '*', '+', '?', '|', '\\'});
}

int Parser::peek() noexcept {
    return *_ptr;
}
