#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void generatePasswords(string current, int length, int maxLength, bool& found);
bool tryPassword(const string& password);
void tryWordlistPasswords(bool& found);

int main() {
    cout << "Brute force program by EBAD MAHAR for educational purposes" << endl;

    cout << "\nAre you sure you want to do this? (YES/NO): ";
    string userInput;
    cin >> userInput;

    if (userInput != "yes") {
        cout << "Thank you for using our services." << endl;
        return 0;
    }

    cout << "\nChoose method (1. Word list 2. Automatic): ";
    int method;
    cin >> method;

    bool found = false;

    if (method == 1) {
        tryWordlistPasswords(found);
    } else {
        int maxLength = 5;
        for (int length = 1; length <= maxLength && !found; ++length) {
            generatePasswords("", length, maxLength, found);
        }
    }

    if (!found) {
        cout << "Password not found." << endl;
    } else {
        cout << "Please donate on Patreon if you like my work and want me to continue it." << endl;
    }

    return 0;
}

void generatePasswords(string current, int length, int maxLength, bool& found) {
    static const string chars = "abcdefghijklmnopqrstuvwxyz";
    if (current.length() == length) {
        if (tryPassword(current)) {
            cout << "Password found: " << current << endl;
            found = true;
        } else {
            cout << current << " is not the password" << endl;
        }
        return;
    }
    for (char c : chars) {
        if (found) return;
        generatePasswords(current + c, length, maxLength, found);
    }
}

bool tryPassword(const string& password) {
    string command = "unrar x -p" + password + " example.rar > nul 2>&1";
    int result = system(command.c_str());

    return result == 0;
}

void tryWordlistPasswords(bool& found) {
    ifstream wordlist("wordlist.txt");
    if (!wordlist.is_open()) {
        cout << "Failed to open wordlist.txt" << endl;
        return;
    }

    string password;
    while (getline(wordlist, password) && !found) {
        if (tryPassword(password)) {
            cout << "Password found: " << password << endl;
            found = true;
        } else {
            cout << password << " is not the password" << endl;
        }
    }

    wordlist.close();
}
