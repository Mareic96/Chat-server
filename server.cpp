#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include <sstream>
#include "crow_all.h"
#include "sqliteDatabase.h"


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


int main(int argc, char* argv[]){
	string senderName = "Mareic1076";
	string recieverName = "Emre26995";
	
	crow::SimpleApp app;
	
	CROW_ROUTE(app, "/")
	([](){
		return "<div><h1>Hello, Welcome to the chat server.</h1><div>";
	});

	CROW_ROUTE(app, "/user/<string>")([recieverName](string senderName){
			string m = read_messages(senderName, recieverName);
			cout << m << "\n";
			return crow::response(m);
			});
	CROW_ROUTE(app, "/user")([senderName, recieverName](){
			crow::json::wvalue x;
			x[senderName] = read_messages(senderName, recieverName);
			return x;
			});

	//a crow rout take a username and list/read all the messages for that user.
	//message_count
	//check_function
	app.port(18080).multithreaded().run();
	//cout << read_messages(senderName, recieverName);

}
