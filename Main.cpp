#include "Username.h"
using std::string;
#include "sqliteDatabase.h"
#include <iostream>
using std::cout;
using std::cin;
#include <ctime>
using std::time;

void login(string username, string password){
	cout << "Please enter your username: ";
	cin >> username;
	cout << "Please enter your password and press enter: ";
	cin >> password;
	check(username, password);
}

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



int main() {
	string firstName;
	string lastName;
	string password;
	char currentUser;
	string username;

	srand((signed)time(0));
	int i = rand();
	string identification = std::to_string (i);

	cout << "Do you already have an account? [Y/N]";
	cin >> currentUser;
	if (currentUser == 'Y' || currentUser == 'y') {
		login(username, password);
	}
	else {
		registration(firstName, lastName, password, identification);
	}


	
	
	

	return 0;

}