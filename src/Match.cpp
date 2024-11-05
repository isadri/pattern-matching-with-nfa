#include <Match.hpp>
#include <NFASim.hpp>
#include <fstream>
#include <iostream>
#include <unistd.h>

char*   Match::_re;

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
        if (NFASim::run(_re, line.c_str()))
            display(line, -1);
        write(1, "\033[1;33m>>\033[0m ", 14);
    }
}

void    Match::from_file(const char* file) {
    std::ifstream   infile(file);

    if (!infile.is_open()) {
        std::cerr << "error: cannot open file!" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::string line;
    size_t      nline{ 0 };

    while (std::getline(infile, line)) {
        ++nline;
        if (NFASim::run(_re, line.c_str()))
            display(line, nline);
    }
}

void    Match::display(const std::string& text, ssize_t nline) {
    const size_t    index = text.find_first_not_of(" \t");
    std::string     trimmed(text.substr(index));

    if (nline == -1) {
        std::cout << "    \033[32m->\033[0m " << trimmed;
    }
    else {
        std::cout << "\033[35m" << std::setw(8) << nline
                << " \033[32m|\033[0m " << trimmed;
    }
    std::cout << "\033[0m\n";
}
