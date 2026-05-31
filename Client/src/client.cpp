#include "client.hpp"
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

void client::new_connection() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0) return perror("Socket creation failed");

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port   = htons(this->s_port);

    if (inet_pton(AF_INET, this->s_ip.c_str(), &serverAddr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        close(clientSocket);
        return;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        close(clientSocket);
        return;
    }

    this->current_wd = this->send_command(clientSocket, "pwd");

    if (!current_wd.empty() && current_wd.back() != '\n') current_wd.pop_back();

    this->command_procedure(clientSocket);
};

void client::enter_command() {
    std::cout << this->current_wd << "> ";
    std::getline(std::cin, this->command);
};

void client::command_procedure(int clientSocket) {
    while(clientSocket) {
        this->enter_command();
        std::string response = send_command(clientSocket, this->command.c_str());
        
        //Check CD
        if (this->command.rfind("cd", 0) == 0) {
            if (response.rfind("ERROR:", 0) != 0) {
                this->current_wd = response;
                if (!current_wd.empty() && current_wd.back() == '\n') current_wd.pop_back();
            } else {
                std::printf("%s", response.c_str());
            }
        } else {
            std::printf("%s", response.c_str());
        }
    }
};

std::string client::send_command(int clientSocket, const char* command) {
    std::string msg(command);
    uint32_t len = htonl(msg.size());

    send(clientSocket, &len, sizeof(len), 0);
    send(clientSocket, msg.c_str(), msg.size(), 0);

    uint32_t resp_len = 0;
    recv(clientSocket, &resp_len, sizeof(resp_len), MSG_WAITALL);
    resp_len = ntohl(resp_len);

    std::string response(resp_len, '\0');
    recv(clientSocket, response.data(), resp_len, MSG_WAITALL);

    return response;
};