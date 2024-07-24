#include "Channel.hpp"
#include "Client.hpp"
#include "Command.hpp"
#include "Server.hpp"
#include "Socket.hpp"
#include "SocketClient.hpp"
#include "SocketServer.hpp"
// jai tout include dans le doute, mais faut voir ce qui est utile
static bool checkPassword(std::string pass) {
    if (pass.empty()) {
        std::cerr << "Error: Password is empty" << std::endl;
        return (false);
    }
    for (size_t i = 0; i < pass.size(); ++i) {
        if (!isalnum(pass[i])) {
            std::cerr << "Error: Password contains non-alphanumeric characters"
                      << std::endl;
            return (false);
        }
    }
    return (true);
}

static int checkPort(char* p) {
    if (*p == '\0') {
        return (6667); // mettre un define c'est + propre
    }

    int port = atoi(p);
    if (port < 1 || port > 65535) {
        std::cerr << "Error: Port has to be between 1 and 65535" << std::endl;
        return (-1);
    }

    return (port);
}

int main(int ac, char** av) {
    if (ac != 3) {
        std::cerr << "Error: Usage: ./ircserv <port> <password>" << std::endl;
        return (EXIT_FAILURE);
    }

    if (checkPort(av[1]) == -1 || !checkPassword(av[2])) {
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}