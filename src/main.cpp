// #include "Command.hpp"
// #include <cstdlib>
// #include <iostream>

int main(int ac, char** av) {
    try {
        Server::getInstance().init(ac, av);
        Server::getInstance().run();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
}
