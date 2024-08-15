#include "Command.hpp"
#include <cstdlib>
#include <iostream>

int main(void) {
    std::string str = "INV user #channel\r\n";

    Command::create(str);
    return (EXIT_SUCCESS);
}
