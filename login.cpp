#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

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
    ofstream file("users.txt", ios::app);
    file << username << "," << password << endl;
    cout << "Signup successful." << endl;
}

bool login() {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        if (line == username + "," + password) {
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
    if (!isUsernameTaken(username)) {
        cout << "Invalid username. Please try again." << endl;
        return;
    }
    ifstream fileIn("users.txt");
    ofstream fileOut("temp.txt", ios::app);
    string line;
    bool found = false;
    while (getline(fileIn, line)) {
        if (line == username + "," + oldPassword) {
            found = true;
            cout << "Enter your new password: ";
            cin >> newPassword;
            fileOut << username << "," << newPassword << endl;
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
    auto start = chrono::high_resolution_clock::now();
    do {
        cout << "Choose an option:" << endl;
        cout << "1. Signup" << endl;
        cout << "2. Login" << endl;
        cout << "3. Reset password" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                if (login()) {
                    cout << "You have logged in!" << endl;
                }
                break;
            case 3:
                resetPassword();
                break;
            case 4:
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Total time taken: " << elapsed.count() << " seconds." << endl;
    return 0;
}
