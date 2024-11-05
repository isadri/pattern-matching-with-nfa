#pragma

#include <string>
#include <vector>

class   Match {
public:
    Match() = delete;

    static void match(const char* re, const char* file);

private:
    static char*                                    _re;
    static std::vector<std::pair<size_t, size_t>>   _positions;
    static std::vector<int>                         _lines;

    static void from_prompt();
    static void from_file(const char* file);
    static void match_line(const char* line);
    static void display(const char* text, ssize_t nline);
};

