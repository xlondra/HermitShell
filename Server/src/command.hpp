#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>

class command {
    public:
        static std::string execute_command(const char* command);
        static std::string previous_path;

    private:
        static std::string handle_cd(const std::string& command);
        static bool is_cd(const std::string& command);
};

#endif