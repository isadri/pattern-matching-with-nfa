#include <iostream>
#include "../include/NFASim.hpp"

[[ noreturn ]] void usage_error(const char* arg) {
    std::cerr << "usage: " << arg << " <regexp> <file>?" << std::endl;
    std::exit(1);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        usage_error(argv[0]);
    }
    try {
        if (NFASim::match(argv[1], argv[2]))
            std::cout << "accepted: " << argv[1] << '\n';
        else
            std::cout << "not accepted: " << argv[1] << '\n';
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

}
