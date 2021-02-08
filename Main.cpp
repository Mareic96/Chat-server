#include "Username.h"
using std::string;
#include "sqliteDatabase.h"
#include <iostream>
using std::cout;
using std::cin;
#include <ctime>
using std::time;


void registration(string firstName, string lastName, string password, string identification) {
	cout << "Please enter your first name and then press enter: ";
	std::cin >> firstName;
	std::cout << "\n";
	std::cout << "Please enter your last name and then press enter: ";
	std::cin >> lastName;
	std::cout << "Please enter your password and press enter: ";
	std::cin >> password;

	Registration p1(firstName, lastName, password);
	{
		Username user(firstName, lastName, password, firstName + identification);
		string username = user.getUser();
		std::cout << username + "\n";
		data(username, firstName, lastName, password);
	}
}



string login(string username, string password) {
	bool again = true;
	while (again == true) {
		std::cout << "Please enter your username: ";
		std::cin >> username;
		std::cout << "Please enter your password and press enter: ";
		std::cin >> password;
		if (login_check(username, password)) {
			again = false;
		}
	}
	return username;
}

//string reciever() {
//	//Do you want to read or write a message. Make a wrap around with an if statement
//	string recieverName;
//	bool found = true;
//	char readOrWrite;
//	std::cout << "Type 'R' if you would like to read a message or type 'W' if you would like to write a message: ";
//	std::cin >> readOrWrite;
//	while (found) {
//		if (readOrWrite == 'W' || readOrWrite == 'w') {
//			std::cout << "Who do you want to send the message to? ";
//			std::cin >> recieverName;
//			if (check(recieverName) == true) {
//				std::cout << "User account found\n";
//				found = false;
//			}
//			else {
//				std::cout << "User account not found, please try again\n";
//			}
//		}
//
//		if (readOrWrite == 'R' || readOrWrite == 'r') {
//			std::cout << "Whose message do you want to read? ";
//			std::cin >> recieverName;
//			if (check(recieverName) == true) {
//				std::cout << "User account found\n";
//				found = false;
//			}
//			else {
//				std::cout << "User account not found, please try again\n";
//			}
//		}
//	}
//	return recieverName;
//}

string writeMessages() {
	string recieverName;
	bool found = true;
	char readOrWrite;
	while (found) {
		std::cout << "Who do you want to send the message to? ";
		std::cin >> recieverName;
		if (check(recieverName) == true) {
			std::cout << "User account found\n";
			found = false;
		}
		else {
			std::cout << "User account not found, please try again\n";
		}
	}

	return recieverName;
}

string readMessages() {
	string recieverName;
	bool found = true;
	char readOrWrite;
	std::cout << "Whose message do you want to read? ";
	std::cin >> recieverName;
	while (found) {
		if (check(recieverName) == true) {
			std::cout << "User account found\n";
			found = false;
		}
		else {
			std::cout << "User account not found, please try again\n";
		}
	}

	return recieverName;
}



int main() {
	string firstName;
	string lastName;
	string password;
	char currentUser;
	string username;
	string message;
	char readOrWrite;
	string senderName;
	string recieverName;
	

	srand((signed)time(0));
	int i = rand();
	string identification = std::to_string (i);


	std::cout << "Do you already have an account? [Y/N]";
	std::cin >> currentUser;
	if (currentUser == 'Y' || currentUser == 'y') {
		senderName = login(username, password);
	}
	else {
		registration(firstName, lastName, password, identification);
	}


	//Do you want to read or write a message. Make a wrap around with an if statement
	std::cout << "Type 'R' if you would like to read a message or type 'W' if you would like to write a message: ";
	std::cin >> readOrWrite;
	if (readOrWrite == 'W' || readOrWrite == 'w') {
		recieverName = writeMessages();
		std::cout << "You can now write your message: ";
		std::cin.ignore(1, '\n');
		std::getline(std::cin, message);
		store_message(senderName, recieverName, message);
	}
	if (readOrWrite == 'R' || readOrWrite == 'r') {
		recieverName = readMessages();
		read_messages(senderName, recieverName);
	}


	
	return 0;

}