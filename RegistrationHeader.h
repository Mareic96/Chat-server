#pragma once
#include <string>

class Registration {
private:
	std::string firstName;
	std::string lastName;
	std::string password;
	
public:
	Registration(std::string first, std::string last, std::string pass);
	std::string getName();
};