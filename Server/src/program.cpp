#include "shell.hpp"

int main() {
    int LISTENING_PORT = 8000; //Change this

    shell shell(LISTENING_PORT);
    shell.start();

    return 0;
}