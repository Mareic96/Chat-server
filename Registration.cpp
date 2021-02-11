#include "RegistrationHeader.h"
#include <string>
using std::string;
#include <iostream>
using std::cout;

Registration::Registration(string first, string last, string pass) :firstName(first), lastName(last), password(pass){}

string Registration::getName() {
	return firstName + " " + lastName;
}
