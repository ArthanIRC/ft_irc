#include "include/Message.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>

int main() {
    std::string str;
    std::vector<std::string> test_cases;

    test_cases.push_back(
        ":Nick!user@host PRIVMSG #channel :Hello, this is a message!"); // Should
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
    test_cases
        .push_back(
            ":Nick!user@host PRIVMSG #channel :Message with newline\nAnother "
            "line"); // Should Fail (newline not allowed)
    test_cases.push_back(":Nick!user@host PING"); // Should Pass
    test_cases.push_back(":Nick@host PRIVMSG #channel :Message with missing "
                         "user"); // Should Pass (prefix without user is valid)
    test_cases
        .push_back(":Nick!user@host PRIVMSG :#channel Trailing parameter in "
                   "wrong place"); // Should Fail (target in trailing parameter)
    test_cases.push_back(":Nick!user@host PRIVMSG #channel:Trailing parameter "
                         "with no space"); // Should Fail (missing space)
    test_cases.push_back(":Nick!user@hostPRIVMSG #channel :Missing space after "
                         "prefix"); // Should Fail (missing space)

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