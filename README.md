# pattern-matching-with-nfa
A flexible pattern matching implementation using Non-deterministic Finite Automata (NFA). This project provides an efficient way to perform pattern matching by converting patterns into NFAs and using them to search through text, implemented in modern C++.

##  Features
* Pattern to NFA conversion
* Efficient text searching using NFA
* Support for common pattern matching operators:
    * Concatenation
    * Union (|)
    * Kleene star (*)
    * Optional character (?)
* Memory-efficient NFA implementation
* Header-only library option
* Modern C++ implementation (C++17)
* No external dependencies

## Prerequisites
* C++17 compatible compiler (GCC 7+, Clang 5+, or MSVC 2017+)
* CMake 3.12 or higher
* Git (for cloning the repository)

## Building the Project

### Linux/macOS
```bash
# Clone the repository
git clone https://github.com/isadri/pattern-matching-with-nfa.git
cd pattern-matching-with-nfa

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make
```

### Windows
```bash
# Clone the repository
git clone https://github.com/isadri/pattern-matching-with-nfa.git
cd pattern-matching-with-nfa

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build . --config Release
```

## Usage

