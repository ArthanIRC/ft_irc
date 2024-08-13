#include "Command.hpp"
#include <cstdlib>

int main(void) {
    std::string str = ":Nick!user@host PASS secret_password\r\n";

    Command::create(str);
    return (EXIT_SUCCESS);
}