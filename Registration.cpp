#include "RegistrationHeader.h"
#include <string>
using std::string;
#include <iostream>
using std::cout;

Registration::Registration(string first, string last, string pass, int id) :firstName(first), lastName(last), password(pass), idNumber(id){}

string Registration::getName() {
	return firstName + " " + lastName;
}

int Registration::getNumber() {
	return idNumber;
}