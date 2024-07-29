#include "include/Message.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>

int main() {
    std::vector<std::string> test_cases;

    // Adding \r\n to the end of each valid test case
    test_cases.push_back(":Nick!user@host PRIVMSG #general :Hello, this is a "
                         "message!\r\n"); // Should Pass1
    test_cases.push_back(
        ":AnotherNick!anotheruser@anotherhost JOIN #help\r\n"); // Should Pass2
    test_cases.push_back(
        ":InvalidNick!user@host INVALIDCOMMAND #salut :Hello!\r\n"); // Should
                                                                     // Pass3
    test_cases.push_back(
        "PRIVMSG #general :Message without prefix\r\n"); // Should Pass4
    test_cases.push_back(
        ":Nick!user@host NOTICE #help :This is a notice\r\n"); // Should Pass5
    test_cases.push_back(
        ":Nick!user@host PRIVMSG :No channel but message\r\n"); // Should Fail66
    test_cases.push_back(
        ":Nick!user@host PRIVMSG #general\r\n"); // Should Fail7
    test_cases.push_back(
        ":Nick!user@host PRIVMSG #salut :\r\n"); // Should Pass8
    test_cases.push_back(":Nick!user@host PRIVMSG #special :Special characters "
                         "!@#$%^&*()\r\n"); // Should Pass9
    test_cases.push_back(":Nick!user@host PRIVMSG #newchannel :Message with "
                         "newline\nAnother line\r\n"); // Should Fail10
    test_cases.push_back(":Nick!user@host PING\r\n");  // Should Pass11
    test_cases.push_back(
        ":Nick@host PRIVMSG #general :Message with missing user\r\n"); // Should
                                                                       // Pass12
    test_cases.push_back(":Nick!user@host PRIVMSG #general :#salut Trailing "
                         "parameter in wrong place\r\n"); // Should Fail13
    test_cases.push_back(":Nick!user@host PRIVMSG #general:Trailing parameter "
                         "with no space\r\n"); // Should Fail14
    test_cases.push_back(":Nick!user@hostPRIVMSG #salut :Missing space after "
                         "prefix\r\n"); // Should Fail15
    test_cases.push_back("PRIVMSG #random :Just a trailing message without "
                         "prefix\r\n"); // Should
                                        // Pass16
    test_cases.push_back(
        "PING :This is a ping with a trailing message\r\n");  // Should Pass17
    test_cases.push_back("JOIN #random\r\n");                 // Should Pass18
    test_cases.push_back("PONG :Response with trailing\r\n"); // Should Pass19
    test_cases.push_back(
        "PRIVMSG :No channel but message\r\n");        // Should Fail20
    test_cases.push_back("PRIVMSG #random :\r\n");     // Should Pass21
    test_cases.push_back("PART #random :Goodbye\r\n"); // Should Pass22
    test_cases.push_back("NICK :NewNickname\r\n");     // Should Pass23
    test_cases.push_back("NICK\r\n");                  // Should Pass24
    test_cases.push_back("NICK :\r\n");                // Should Pass25
    test_cases.push_back("QUIT :Leaving\r\n");         // Should Pass26
    test_cases.push_back("QUIT\r\n");                  // Should Pass27

    // Adding one test case without \r\n at the end
    test_cases.push_back("PRIVMSG #missing_trailing"); // Should Fail28

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