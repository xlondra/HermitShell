#include "client.hpp"
#include <iostream>


int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <ip> <port>" << std::endl;
        return 1;
    }

    std::string connect_to = argv[1];
    int port = std::stoi(argv[2]);

    client client(connect_to, port);
    client.new_connection();
}