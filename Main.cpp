#include "Username.h"
using std::string;
#include "sqliteDatabase.h"
#include <iostream>
using std::cout;
using std::cin;
#include <ctime>
using std::time;

int main() {
	string firstName;
	string lastName;
	string passWord;

	srand(time(0));
	int i = rand();
	string identification = std::to_string (i);

	cout << "Please enter your first name and then press enter: ";
	cin >> firstName;
	cout << "\n";
	cout << "Please enter your last name and then press enter: ";
	cin >> lastName;
	cout << "Please enter your password and press enter: ";
	cin >> passWord;

	Registration p1(firstName, lastName, passWord, i);
	{
		Username user(firstName, lastName, passWord, i, firstName + identification);
		string username = user.getUser();
		cout << username + "\n";
	}

	data();
	
	

	return 0;

}