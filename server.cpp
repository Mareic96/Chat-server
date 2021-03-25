#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include <sstream>
#include <vector>
#include "crow_all.h"
#include "sqliteDatabase.h"
#include "base64.h"




bool login(string username, string password) {
	cout << username << "\n";
	cout << password << "\n";
        if (login_check(username, password)) {
		return true;
	}
	else{
		return false;
	}	
	
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
		return "<div><h1>Hello, Welcome to the chat server.<h1><div>";
	});

	CROW_ROUTE(app, "/login").methods("POST"_method)([](const crow::request& req){
			//This is where you will decode the username
			//Check if it exist in the database
			string authValue = req.get_header_value("Authorization");
			printf("%s\n",authValue.c_str());
			int spaces = authValue.find(" ");
			string pass = base64_decode(authValue.substr(spaces + 1), false);
			cout << pass << "\n";

			int colonLoc = pass.find(":");
			string userName = pass.substr(0,colonLoc);
			string passWord = pass.substr(colonLoc + 1);
			//cout << userName << " " << passWord << "\n";
			bool results = login_check(userName, passWord);
			int result = (int)results;
			printf("%d\n", results);
			if(results == false){
				return crow::response(401);
					}
			return crow::response(200);
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
