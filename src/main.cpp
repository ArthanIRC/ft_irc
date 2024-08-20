#include <bits/types/sigset_t.h>
#include <csignal>
#include <cstdlib>
#include <exception>

#include "Server.hpp"

static void handle_signint(int signal) {
    (void)signal;
    Server::getInstance().stop();
}

static int register_sigaction(int signal, void (*handler)(int)) {
    struct sigaction action;
    sigset_t set;

    sigemptyset(&set);
    action.sa_handler = handler;
    action.sa_mask = set;
    action.sa_flags = 0;
    if (sigaction(signal, &action, NULL) == -1) {
        std::cerr << "Error: sigaction creation failed\n";
        return -1;
    }
    return 0;
}

int main(int ac, char** av) {
    if (register_sigaction(SIGINT, &handle_signint) == -1 ||
        register_sigaction(SIGQUIT, SIG_IGN) == -1)
        return EXIT_FAILURE;

    try {
        Server::getInstance().init(ac, av);
        Server::getInstance().run();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
}
