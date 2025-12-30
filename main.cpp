#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
    while (true) {
        std::cout << "\nWhich test would you like to run?\n"
             << "  1) lasdtest()\n"
             << "  2) mytest()\n"
             << "Enter your choice (or q to quit): ";

        char choice;
        std::cin >> choice;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input, please try again.\n";
            continue;
        }

        if (choice == 'q' || choice == 'Q') {
            std::cout << "Goodbye!\n";
            break;
        }

        switch (choice) {
            case '1':
                std::cout << "Running lasdtest()...\n";
                lasdtest();
                break;
            case '2':
                std::cout << "Running mytest()...\n";
                mytest::mytest();
                break;
            default:
                std::cout << "Invalid selection, please enter 1, 2, or q.\n";
                continue;
        }
    }


    return 0;
}