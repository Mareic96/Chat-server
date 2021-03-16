#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include <sstream>
#include "crow_all.h"
#include "sqliteDatabase.h"
#include <vector>



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

        		
int main(int argc, char* argv[]){
	//string senderName = "Mareic1073";
	string receiverName = "Emre26995";
	
	crow::SimpleApp app;
	
	CROW_ROUTE(app, "/")
	([](){
		return "<div><h1>Hello, Welcome to the chat server.</h1><div>";
	});


	CROW_ROUTE(app, "/user/<string>")([receiverName](string senderName){
			crow::json::wvalue x;
			std::vector<string> m = read_messages(senderName, receiverName);
			for(int i = 0; i < m.size(); i++){
				x["Messages"][i] = m.at(i);
				
				}
			return x;
			});


	CROW_ROUTE(app, "/user/<string>/send_messages").methods("POST"_method)([receiverName](const crow::request& req, string senderName){
			auto x = crow::json::load(req.body);
			string message;
			if(!x){
				return crow::response(400);
				}
			//cout << x;

			message = x["message"].s();

			store_message(senderName, receiverName, message);

			
			std::ostringstream os;
			os << message;
        		return crow::response(os.str());
			});




	/*CROW_ROUTE(app, "/user")([senderName, recieverName](){
			crow::json::wvalue x;
			x[senderName] = read_messages(senderName, recieverName);
			return x;
			});*/

	//a crow rout take a username and list/read all the messages for that user.
	//message_count
	//check_function
	app.port(18080).multithreaded().run();
	//cout << read_messages(senderName, recieverName);

}
