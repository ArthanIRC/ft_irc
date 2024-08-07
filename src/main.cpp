#include "Server.hpp"
#include <cstdlib>
#include <exception>

int main(int ac, char** av) {
    try {
        Server s = Server::create(ac, av);
        s.run();
    } catch (std::exception& e) {
        std::cout << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}