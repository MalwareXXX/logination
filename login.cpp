#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
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

bool isUsernameTaken(string username) {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        if (line.substr(0, line.find(",")) == username) {
            return true;
        }
    }
    return false;
}

void signup() {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;
    if (isUsernameTaken(username)) {
        cout << "Username already taken. Please try again." << endl;
        return;
    }
    cout << "Enter a password: ";
    cin >> password;
    string hashed_password = sha256(password);
    ofstream file("users.txt", ios::app);
    file << username << "," << hashed_password << endl;
    cout << "Signup successful." << endl;
}

bool login() {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    string hashed_password = sha256(password);
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        if (line == username + "," + hashed_password) {
            return true;
        }
    }
    cout << "Invalid username or password. Please try again." << endl;
    return false;
}

void resetPassword() {
    string username, oldPassword, newPassword;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your old password: ";
    cin >> oldPassword;
    string hashed_oldPassword = sha256(oldPassword);
    if (!isUsernameTaken(username)) {
        cout << "Invalid username. Please try again." << endl;
        return;
    }
    ifstream fileIn("users.txt");
    ofstream fileOut("temp.txt");
    string line;
    bool found = false;
    while (getline(fileIn, line)) {
        if (line == username + "," + hashed_oldPassword) {
            found = true;
            cout << "Enter your new password: ";
            cin >> newPassword;
            string hashed_newPassword = sha256(newPassword);
            fileOut << username << "," << hashed_newPassword << endl;
            cout << "Password reset successful." << endl;
        }
        else {
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

int main() {
int choice;
do {
cout << "Choose an option:" << endl;
cout << "1. Signup" << endl;
cout << "2. Login" << endl;
cout << "3. Reset Password" << endl;
cout << "4. Exit" << endl;
cin >> choice;
switch (choice) {
case 1:
signup();
break;
case 2:
if (login()) {
cout << "Login successful." << endl;
}
break;
case 3:
resetPassword();
break;
case 4:
cout << "Goodbye!" << endl;
break;
default:
cout << "Invalid choice. Please try again." << endl;
break;
}
} while (choice != 4);
return 0;
}