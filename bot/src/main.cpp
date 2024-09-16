#include <csignal>
#include <cstdlib>
#include <iostream>

#include "Bot.hpp"

static void handle_signint(int signal) {
    (void)signal;
    Bot::getInstance().stop();
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

    std::setlocale(LC_ALL, "en_US.UTF-8");
    srand(time(0));

    try {
        Bot::getInstance().init(ac, av);
        Bot::getInstance().run();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
}