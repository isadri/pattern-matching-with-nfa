# pattern-matching-with-nfa
A simple pattern matching implementation using Non-Deterministic Finite Automata (NFA). This project provides an efficient way to perform pattern matching by converting patterns into NFAs and using them to search through text, implemented in modern C++.

##  Features
* Represent regular expression as NFAs.
* Efficient text searching using NFA.
* Support for common pattern matching operators:
    * Concatenation.
    * Union (|).
    * Kleene closure (*).
    * Positive closure (+).
    * Optional character (?).
    * Character classes (\w, \d).
    * Wildcard (.).
* Memory-efficient NFA implementation.
* Header-only library option.
* Modern C++ implementation (C++11).
* No external dependencies.

## Prerequisites
* C++11 compatible compiler.
* CMake 3.30 or higher.
* Git (for cloning the repository).

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

