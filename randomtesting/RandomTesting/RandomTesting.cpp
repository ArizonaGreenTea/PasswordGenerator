#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <chrono>
#include <string>

// This stores the users response to the prompt
char reply;

// This variable will toggle whether there are capital letters
// none for no caps, some for a mix, and all for all caps
enum class caps { none, some, all };
// Random Generator
std::default_random_engine generator(time(NULL));
// Range for generator
std::uniform_int_distribution<int> distro(33, 126);

//Function that accepts user input to generate a new random password
std::string NewPassword();

void ViewPasswords();

void FilterCase(caps c, char newChar);

char GenerateNewChar();


int main()
{
    // Display prompt
    std::cout << "1. Generate new password\n2. View all generated passwords\n3. Exit\n"; std::cin >> reply;

    if (reply == '1')
    {
        std::cout << NewPassword();
    }
    else if (reply == '2')
    {
        ViewPasswords();
    }
    else if (reply == '3')
    {
        return 0;
    }
}

std::string NewPassword()
{
    

    // This variable stores the final string we will return as the password
    std::string newPassword = "";

    // Lower and upper character limits for the password
    int minLength, maxLength;
    // Actual selected size of the string based on min and max
    int length;

    // These bools will determine what types of characters we use for the password
    bool numbersToggle = true, lettersToggle = true, symbolsToggle = true;

    // This vector will store all user defined characters to forbid
    std::vector<char> excludedChars;

    // Get Min and Max character bounds
    std::cout << "Enter the minimum character limit: "; std::cin >> minLength;
    std::cout << "Enter the maximum character limit: "; std::cin >> maxLength;

    // This statement draws a random number ranging from the minimum to the maximum
    std::uniform_int_distribution<int> lengthDistro(minLength, maxLength);
    length = lengthDistro(generator);

    // Inquire user about capital letters
    std::cout << "Would you like capital letters? Y/N\n"; std::cin >> reply;
    caps c = caps::none;

    if ((reply == 'Y') || (reply == 'y'))
    {
        std::cout << "All capital letters? Y/N\n"; std::cin >> reply;
        if ((reply == 'Y') || (reply == 'y'))
        {
            c = caps::all;
        }
        else if ((reply == 'N') || (reply == 'n'))
        {
            c = caps::some;
        }
    }
    else if ((reply == 'N') || (reply == 'n'))
    {
        c = caps::none;
    }

    // Ask user for character types
    std::cout << "Use numbers? Y/N\n"; std::cin >> reply;
    if ((reply == 'Y') || (reply == 'y'))
    {
        numbersToggle = true;
    }
    else if ((reply == 'N') || (reply == 'n'))
    {
        numbersToggle = false;
    }

    std::cout << "Use letters? Y/N\n"; std::cin >> reply;
    if ((reply == 'Y') || (reply == 'y'))
    {
        lettersToggle = true;
    }
    else if ((reply == 'N') || (reply == 'n'))
    {
        lettersToggle = false;
    }

    std::cout << "Use symbols? Y/N\n"; std::cin >> reply;
    if ((reply == 'Y') || (reply == 'y'))
    {
        symbolsToggle = true;
    }
    else if ((reply == 'N') || (reply == 'n'))
    {
        symbolsToggle = false;
    }

    std::cout << "Please enter any characters to exclude.\n If there are none press CTRL + Z then hit enter.\n";
    while (std::cin >> reply)
    {
        excludedChars.push_back(reply);
    }


    // Use gathered data to generate a new random password
    // TODO: LEARN STRING MANIPULATION!!!!!
    char newChar;
    for (int i = 0; i < length; i++)
    {
        // Roll a new random character
        newChar = GenerateNewChar();

        // Is this a letter?
        if (isalpha(newChar))
        {
            FilterCase(c, newChar);
        }
        // Is this a number?
        else if (isdigit(newChar))
        {
            if (numbersToggle == false)
            {
                GenerateNewChar();
            }
        }

        // Add the new char to the string
        newPassword.push_back(newChar);
    }
    return newPassword;
}

void ViewPasswords()
{
    std::cout << "TODO: Save Passwords to text file and display them here\n";
}

void FilterCase(caps c, char newChar)
{
    // If caps is set to none, lower any alpha values
    if (c == caps::none)
    {
        tolower(newChar);
    }
    // If caps is set to some, do a 50/50 calculation to determine its case
    else if (c == caps::some)
    {
        if (distro(generator) % 2 == 0)
        {
            tolower(newChar);
        }
        else if (distro(generator) % 2 == 1)
        {
            toupper(newChar);
        }
    }
    // If caps is set to all, capitalize all alpha values
    else if (c == caps::all)
    {
        toupper(newChar);
    }
}

char GenerateNewChar()
{
    return distro(generator);
}

// This is my first time uploading to Github :)
