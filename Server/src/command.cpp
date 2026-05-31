#include "command.hpp"
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <unistd.h>

std::string command::execute_command(const char* command) {
    if (command::is_cd(command)) return command::handle_cd(command);

    std::string cmd_with_stderr = std::string(command) + " 2>&1";
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd_with_stderr.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed");

    while(fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
};

bool command::is_cd(const std::string& command) {
    return command.rfind("cd", 0) == 0;
};

std::string command::handle_cd(const std::string& command) {
    std::string path = command.size() > 3 ? command.substr(3) : "";
    if (path.empty()) {
        const char* home = getenv("HOME");
        if (!home) return "ERROR: HOME not set";
        path = home;
    }

    if (chdir(path.c_str()) == 0) {
        char buffer[4096];
        getcwd(buffer, sizeof(buffer));
        return buffer;
    } else {
        return "ERROR: " + std::string(strerror(errno));
    }
};