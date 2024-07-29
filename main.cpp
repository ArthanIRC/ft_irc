#include "include/Message.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>

int main() {
    std::string str;
    std::vector<std::string> test_cases;

    test_cases.push_back(":Nick!user@host PRIVMSG #channel :Hello, this is a "
                         "message!"); // Should
                                      // Pass
    test_cases.push_back(
        ":AnotherNick!anotheruser@anotherhost JOIN #channel"); // Should Pass
    test_cases.push_back(
        ":InvalidNick!user@host INVALIDCOMMAND #channel :Hello!"); // Should
                                                                   // Pass
                                                                   // (format is
                                                                   // correct)
    test_cases.push_back(
        "PRIVMSG #channel :Message without prefix"); // Should Pass
    test_cases.push_back(
        ":Nick!user@host NOTICE #channel :This is a notice"); // Should Pass
    test_cases.push_back(
        ":Nick!user@host PRIVMSG :No channel but message"); // Should Fail
                                                            // (missing target)
    test_cases.push_back(
        ":Nick!user@host PRIVMSG #channel"); // Should Fail (missing trailing
                                             // message)
    test_cases.push_back(":Nick!user@host PRIVMSG #channel :"); // Should Pass
    test_cases.push_back(":Nick!user@host PRIVMSG #channel :Special characters "
                         "!@#$%^&*()"); // Should Pass
    test_cases.push_back(
        ":Nick!user@host PRIVMSG #channel :Message with newline\nAnother "
        "line"); // Should Fail (newline not allowed)
    test_cases.push_back(":Nick!user@host PING"); // Should Pass
    test_cases.push_back(":Nick@host PRIVMSG #channel :Message with missing "
                         "user"); // Should Pass (prefix without user is valid)
    test_cases.push_back(
        ":Nick!user@host PRIVMSG :#channel Trailing parameter in "
        "wrong place"); // Should Fail (target in trailing parameter)
    test_cases.push_back(":Nick!user@host PRIVMSG #channel:Trailing parameter "
                         "with no space"); // Should Fail (missing space)
    test_cases.push_back(":Nick!user@hostPRIVMSG #channel :Missing space after "
                         "prefix"); // Should Fail (missing space)

    // New test cases
    test_cases.push_back(
        "PRIVMSG #channel :Just a trailing message without prefix"); // Should
                                                                     // Pass
    test_cases.push_back(
        "PING :This is a ping with a trailing message"); // Should Pass
    test_cases.push_back("JOIN #channel"); // Should Pass (valid without prefix)
    test_cases.push_back("PONG :Response with trailing"); // Should Pass
    test_cases.push_back(
        "PRIVMSG :No channel but message"); // Should Fail (missing channel or
                                            // user)
    test_cases.push_back("PRIVMSG #channel :"); // Should Pass (valid with empty
                                                // trailing message)
    test_cases.push_back("PART #channel :Goodbye"); // Should Pass
    test_cases.push_back("NICK :NewNickname");      // Should Pass
    test_cases.push_back(
        "NICK"); // Should Pass (valid, though often the prefix is used)
    test_cases.push_back(
        "NICK :"); // Should Pass (valid with empty trailing message)
    test_cases.push_back("QUIT :Leaving"); // Should Pass
    test_cases.push_back(
        "QUIT"); // Should Pass (valid, though usually with a trailing message)

    for (size_t i = 0; i < test_cases.size(); ++i) {
        std::cout << "Test case " << i + 1 << ": " << test_cases[i]
                  << std::endl;
        try {
            Message::create(test_cases[i]);
            std::cout << "Message format is valid." << std::endl;
        } catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << "------------------------" << std::endl;
    }

    return (EXIT_SUCCESS);
}