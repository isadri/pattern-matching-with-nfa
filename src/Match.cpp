#include <Match.hpp>
#include <NFASim.hpp>
#include <fstream>
#include <iostream>
#include <unistd.h>

char*                                   Match::_re;
std::vector<std::pair<size_t, size_t>>    Match::_positions;

void    Match::match(const char* re, const char* file) {
    _re = const_cast<char*>(re);
    if (!file) {
        from_prompt();
    } else {
        from_file(file);
    }
}

void    Match::from_prompt() {
    std::string line;

    write(1, "\033[1;33m>>\033[0m ", 14);
    while (std::getline(std::cin, line)) {
        start(line.c_str());
        write(1, "\033[1;33m>>\033[0m ", 14);
    }
}

void    Match::from_file(const char* file) {
}

void    Match::start(const char* line) {
    std::string cpy(line);
    char*       token = std::strtok(const_cast<char*>(line), " \t");
    size_t      begin{ 0 };
    size_t      end{ 0 };

    while (token) {
        if (NFASim::match(_re, token)) {
            begin = token - line;
            end = begin + std::strlen(token);
            _positions.push_back({ begin, end });
        }
        token = std::strtok(nullptr, " \t");
    }
    display(cpy.c_str());
    _positions.clear();
}

void    Match::display(const char* text) {
    std::string result;
    size_t      start{ 0 };
    size_t      i{ 0 };

    while (text[i]) {
        if (start < _positions.size() && i == _positions[start].first) {
            result += "\033[32m";
            while (i < _positions[start].second && text[i])
                result += text[i++];
            result += "\033[0m";
            start++;
        }
        else {
            result += text[i++];
        }
    }
    i = 0;
    std::cout << "    \033[32m->\033[0m " << result << '\n';
    std::cout << "       \033[32m";
    for (start = 0; start < _positions.size(); ++start) {
        for (; i < _positions[start].first; ++i)
            std::cout << '-';
        for (; i < _positions[start].second; ++i)
            std::cout << '^';
    }
    std::cout << "\033[0m\n";
}
