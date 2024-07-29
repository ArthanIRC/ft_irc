#include "include/Message.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>

int main() {
    std::vector<std::string> test_cases;
    test_cases.push_back(":Nick!user@host PRIVMSG #general :Hello, this is a "
                         "message!"); // Should
                                      // Pass
    test_cases.push_back(
        ":AnotherNick!anotheruser@anotherhost JOIN #help"); // Should Pass
    test_cases.push_back(
        ":InvalidNick!user@host INVALIDCOMMAND #salut :Hello!"); // Should Pass
    test_cases.push_back(
        "PRIVMSG #general :Message without prefix"); // Should Pass
    test_cases.push_back(
        ":Nick!user@host NOTICE #help :This is a notice"); // Should Pass
    test_cases.push_back(
        ":Nick!user@host PRIVMSG :No channel but message");   // Should Fail
    test_cases.push_back(":Nick!user@host PRIVMSG #general"); // Should Fail
    test_cases.push_back(":Nick!user@host PRIVMSG #salut :"); // Should Pass
    test_cases.push_back(":Nick!user@host PRIVMSG #special :Special characters "
                         "!@#$%^&*()"); // Should Pass
    test_cases.push_back(":Nick!user@host PRIVMSG #newchannel :Message with "
                         "newline\nAnother line"); // Should Fail
    test_cases.push_back(":Nick!user@host PING");  // Should Pass
    test_cases.push_back(
        ":Nick@host PRIVMSG #general :Message with missing user"); // Should
                                                                   // Pass
    test_cases.push_back(":Nick!user@host PRIVMSG #general :#salut Trailing "
                         "parameter in wrong place"); // Should Fail
    test_cases.push_back(":Nick!user@host PRIVMSG #general:Trailing parameter "
                         "with no space"); // Should Fail
    test_cases.push_back(
        ":Nick!user@hostPRIVMSG #salut :Missing space after prefix"); // Should
                                                                      // Fail
    test_cases.push_back(
        "PRIVMSG #random :Just a trailing message without prefix"); // Should
                                                                    // Pass
    test_cases.push_back(
        "PING :This is a ping with a trailing message");     // Should Pass
    test_cases.push_back("JOIN #random");                    // Should Pass
    test_cases.push_back("PONG :Response with trailing");    // Should Pass
    test_cases.push_back("PRIVMSG :No channel but message"); // Should Fail
    test_cases.push_back("PRIVMSG #random :");               // Should Pass
    test_cases.push_back("PART #random :Goodbye");           // Should Pass
    test_cases.push_back("NICK :NewNickname");               // Should Pass
    test_cases.push_back("NICK");                            // Should Pass
    test_cases.push_back("NICK :");                          // Should Pass
    test_cases.push_back("QUIT :Leaving");                   // Should Pass
    test_cases.push_back("QUIT");                            // Should Pass

    for (size_t i = 0; i < test_cases.size(); ++i) {
        std::cout << "Test case " << (i + 1) << ": " << test_cases[i]
                  << std::endl;
        try {
            std::string data = test_cases[i];
            Message::create(data);
            std::cout << "Message format is valid." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << "------------------------" << std::endl;
    }

    return 0;
}