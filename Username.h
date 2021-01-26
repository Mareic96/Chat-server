#pragma once
#include "RegistrationHeader.h"
#include <string>

class Username : public Registration {
private:
	std::string user;
public:
	Username(std::string first, std::string last, std::string pass, int id, std::string tag);
	std::string getUser();
};