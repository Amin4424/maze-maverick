#include <iostream>
#include <conio.h> // include for getch()
#include <stdlib.h>

int main() {
    char choice;

    do {
        std::cout << "Menu:\n";
        std::cout << "1. Option 1\n";
        std::cout << "2. Option 2\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";

        choice = _getch(); // Get a single character input

        switch (choice) {
            case '1': 
                system("cls"); // Clear the screen
                std::cout << "You chose Option 1\n";
                // Code for option 1
                break;
            case '2':
                system("cls"); // Clear the screen
                std::cout << "You chose Option 2\n";
                // Code for option 2
                break;
            case '3':
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice\n";
                break;
        }
        std::cout << std::endl;
    } while (choice != '3');

    return 0;
}
