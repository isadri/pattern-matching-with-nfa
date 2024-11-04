#pragma

#include <string>
#include <vector>

class   Match {
public:
    Match() = delete;

    static void match(const char* re, const char* file);

private:
    static char*                                _re;
    static std::vector<std::pair<size_t, size_t>> _positions;

    static void from_prompt();
    static void from_file(const char* file);
    static void start(const char* line);
    static void display(const char* text);
};

