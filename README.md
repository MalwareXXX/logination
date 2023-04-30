# Logination

This is a simple program that allows users to sign up, log in, and reset their password. User credentials are stored in a file called `users.txt`. Passwords are hashed using the SHA256 algorithm before they are stored in the file.

## Requirements

- C++ compiler
- OpenSSL library

## How to Use

1. Clone the repository to your local machine:
git clone https://github.com/your-username/logination.git


2. Compile the program:
g++ login.cpp -lcrypto -o login
Note: The `-lcrypto` flag is required to link the OpenSSL library.

3. Run the program:
./login
You will be prompted to sign up, log in, or reset your password.

## Contributors

- [MalwareXXX](https://github.com/malwarexxx)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.


