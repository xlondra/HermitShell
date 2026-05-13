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

    if (bind(serverSocket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind failed");
        close(serverSocket);
        return;
    }

    listen(serverSocket, 5);

    this->acceptClientConnection(serverSocket);
}

void shell::acceptClientConnection(int serverSocket)
{
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    while (clientSocket) {
        char buffer[1024] = {0};
        recv(clientSocket, buffer, sizeof(buffer), 0);

        std::string output = command::execute_command(buffer);

        send(clientSocket, output.data(), output.size(), 0);
    }
}