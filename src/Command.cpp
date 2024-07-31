#include "Command.hpp"
#include <exception>
#include <iostream>

Command* Command::create(std::string& data) {
    try {
        if (!Message::verify(data))
            std::cerr << "Error: " << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    // try {
    //     Message* msg = new PrivMessageCommand(data);
    //     return msg;
    // } catch (..) {
    // }

    // try {
    //     Message* msg = new JoinCommand(data);
    //     return msg
    // } catch (..) {
    // }
}