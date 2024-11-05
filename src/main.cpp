#include <iostream>
#include <Match.hpp>

[[ noreturn ]] void usage_error(const char* arg) {
    std::cerr << "usage: " << arg << " <regexp> <file>?" << std::endl;
    std::exit(1);
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3)
        usage_error(argv[0]);

    try {
        Match::match(argv[1], argv[2]);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::exit(EXIT_FAILURE);
    }
    std::exit(EXIT_SUCCESS);
}
