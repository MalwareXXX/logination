#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <openssl/sha.h>

using namespace std;

string sha256(const string str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

bool isUsernameTaken(string username, unordered_map<string, string>& users) {
    return users.find(username) != users.end();
}

string generateRandomPassword(int length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string password = "";
    srand(time(NULL));
    for (int i = 0; i < length; ++i) {
        password += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return password;
}

void signup(unordered_map<string, string>& users) {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;
    if (isUsernameTaken(username, users)) {
        cout << "Username already taken. Please try again." << endl;
        return;
    }
    cout << "Would you like to generate a random password? (Y/N) ";
    char choice;
    cin >> choice;
    if (tolower(choice) == 'y') {
        int length;
        cout << "Enter the length of the password: ";
        cin >> length;
        password = generateRandomPassword(length);
        cout << "Generated password: " << password << endl;
    } else {
        cout << "Enter a password: ";
        cin >> password;
    }
    string hashed_password = sha256(password);
    users[username] = hashed_password;
    ofstream file("users.txt", ios::app);
    file << username << "," << hashed_password << endl;
    cout << "Signup successful." << endl;
}

bool login(unordered_map<string, string>& users) {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    string hashed_password = sha256(password);
    if (users.find(username) != users.end() && users[username] == hashed_password) {
        return true;
    }
    cout << "Invalid username or password. Please try again." << endl;
    return false;
}

void resetPassword(unordered_map<string, string>& users) {
    string username, oldPassword, newPassword;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your old password: ";
    cin >> oldPassword;
    string hashed_oldPassword = sha256(oldPassword);
    if (!isUsernameTaken(username, users)) {
        cout << "Invalid username. Please try again." << endl;
        return;
    }
    cout << "Enter your new password: ";
    cin >> newPassword;
    string hashed_newPassword = sha256(newPassword);
    fileOut << username << "," << hashed_newPassword << endl;
    cout << "Password reset successful." << endl;
            found = true;
        } else {
            fileOut << line << endl;
        }
    }
    fileIn.close();
    fileOut.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (!found) {
        cout << "Invalid username or password. Please try again." << endl;
    }
}
