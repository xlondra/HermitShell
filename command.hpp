#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>

class command {
    public:
        static std::string execute_command(const char* command);
};

#endif