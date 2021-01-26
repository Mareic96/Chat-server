#pragma once
#include <string>

class Registration {
private:
	std::string firstName;
	std::string lastName;
	std::string password;
	int idNumber;
public:
	Registration(std::string first, std::string last, std::string pass, int id);
	std::string getName();
	int getNumber();
};