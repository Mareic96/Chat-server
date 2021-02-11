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
	cin >> firstName;
	cout << "\n";
	cout << "Please enter your last name and then press enter: ";
	cin >> lastName;
	cout << "Please enter your password and press enter: ";
	cin >> password;

	Registration p1(firstName, lastName, password);
	{
		Username user(firstName, lastName, password, firstName + identification);
		string username = user.getUser();
		cout << username + "\n";
		data(username, firstName, lastName, password);
	}
}



string login(string username, string password) {
	bool again = true;
	while (again == true) {
		cout << "Please enter your username: ";
		cin >> username;
		cout << "Please enter your password and press enter: ";
		cin >> password;
		if (login_check(username, password)) {
			again = false;
		}
	}

	return username;
}


string writeMessages() {
	string recieverName;
	bool found = true;
	while (found) {
		cout << "Who do you want to send the message to? ";
		cin >> recieverName;
		if (check(recieverName) == true) {
			cout << "User account found\n";
			found = false;
		}
		else {
			cout << "User account not found, please try again\n";
		}
	}

	return recieverName;
}

string readMessages() {
	string recieverName;
	bool found = true;
	while (found) {
		cout << "Whose message do you want to read? ";
		cin >> recieverName;
		if (check(recieverName) == true) {
			cout << "User account found\n";
			found = false;
		}
		else {
			cout << "User account not found, please try again\n";
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


	cout << "Do you already have an account? [Y/N]";
	cin >> currentUser;
	if (currentUser == 'Y' || currentUser == 'y') {
		senderName = login(username, password);
	}
	else {
		registration(firstName, lastName, password, identification);
	}


	//Do you want to read or write a message. Make a wrap around with an if statement
	cout << "Type 'R' if you would like to read a message or type 'W' if you would like to write a message: ";
	cin >> readOrWrite;
	if (readOrWrite == 'W' || readOrWrite == 'w') {
		recieverName = writeMessages();
		cout << "You can now write your message: ";
		cin.ignore(1, '\n');
		std::getline(cin, message);
		store_message(senderName, recieverName, message);
	}
	if (readOrWrite == 'R' || readOrWrite == 'r') {
		read_receipts(senderName);
		recieverName = readMessages();
		read_messages(senderName, recieverName);
		//Maybe write another database function to count the amount of messages.
	}


	
	return 0;

}