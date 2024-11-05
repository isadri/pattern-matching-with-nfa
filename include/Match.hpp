#pragma

#include <string>
#include <vector>

class   Match {
public:
    Match() = delete;

    static void match(const char* re, const char* file);

private:
    static char*    _re;

    static void from_prompt();
    static void from_file(const char* file);
    static void display(const std::string& text, ssize_t nline);
};

