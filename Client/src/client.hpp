#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class client {
    public:
        int s_port;
        std::string s_ip;

        void new_connection();

        client(std::string ip, int port) {
            this->s_port = port;
            this->s_ip = ip;
        }

    private:
        void enter_command();
        void command_procedure(int clientSocket);

        std::string current_wd;
        std::string send_command(int clientSocket, const char* command);
        std::string command;
};


#endif