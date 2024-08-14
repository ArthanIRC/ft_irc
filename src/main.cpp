#include "Command.hpp"
#include <cstdlib>

int main(void) {
    std::string str = "PASS secret_password\n";

    Command::create(str);
    return (EXIT_SUCCESS);
}