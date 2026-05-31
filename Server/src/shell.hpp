#ifndef SHELL_HPP
#define SHELL_HPP

class shell {
    public:
        void start();

        int port;

        shell(int _port) {
            this->port = _port;
        }

    private:
        void acceptClientConnection(int serverSocket);
};

#endif