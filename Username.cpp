#include "RegistrationHeader.h"
#include "Username.h"
#include <string>
using std::string;

Username::Username(string first, string last, string pass, string tag) : Registration(first, last, pass), user(tag) {};

string Username::getUser() {
	return user;
}