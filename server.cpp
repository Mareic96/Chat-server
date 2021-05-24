#include <iostream>
using std::cout;
using std::cin;
#include <string>
using std::string;
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include "crow_all.h"
#include "sqliteDatabase.h"
#include "base64.h"
#include "jwt.h"



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
	std::map<string, string> key{};

	
	crow::SimpleApp app;
	
	CROW_ROUTE(app, "/")
	([](){
		return "<div><h1>Hello, Welcome to the chat server.<h1><div>";
	});

	CROW_ROUTE(app, "/login").methods("POST"_method)([&key](const crow::request& req){
			//This is where you will decode the username
			//Check if it exist in the database
			string authValue = req.get_header_value("Authorization");
			//printf("%s\n",authValue.c_str());
			int spaces = authValue.find(" ");
			string pass = base64_decode(authValue.substr(spaces + 1), false);
			//cout << pass << "\n";

			int colonLoc = pass.find(":");
			string userName = pass.substr(0,colonLoc);
			string passWord = pass.substr(colonLoc + 1);
			//cout << userName << " " << passWord << "\n";
			bool results = login_check(userName, passWord);
			int result = (int)results;
			//printf("%d\n", results);
			if(results == false){
				return crow::response(401);
			}

			std::ifstream file1("../jwtrs256.key.pub");
			std::ifstream file2("../jwtrs256.key");
			if(file1.is_open()){
				cout << "File found\n";
			}
			else {cout << "Unable to print file content\n";}
			
			std::stringstream rsaPublicKey, rsaPrivateKey;
			rsaPublicKey << file1.rdbuf();
			rsaPrivateKey << file2.rdbuf();
			//printf("%s", rsaPublicKey.str().c_str());


			auto token = jwt::create().set_type("JWT")
			.set_issuer("chat_server")
			.set_issued_at(std::chrono::system_clock::now())
			.sign(jwt::algorithm::rs256(rsaPublicKey.str(), rsaPrivateKey.str(), "", ""));
			crow::response success = crow::response(200);
			success.add_header("JWT", token);
			key[userName] = token;
			//cout << "Token: " << key["Mareic1073"] << "\n"; 
			//cout << "Token: " << token << "\n";

			return success;
			});

	


	CROW_ROUTE(app, "/user/<string>")([receiverName, &key](const crow::request& req, string senderName){
			//cout << "Token: " << key[senderName] << "\n";
			//Recieve header value from client
			//get it out of the header field
			//Compare that to senderName
			//return a 401 if its not right
			string authValue = req.get_header_value("Authorization");
			//printf("%s\n", authValue.c_str());
			auto name = key.find(senderName);
			string JWToken = key.find(senderName) -> second;
			if(name == key.end()){
				cout << "Account not found\n";
				return crow::response(401);
			}
			else{
				cout << "Account found" << "\n";
			}
			//add if statement, if name is not equal to authvalue, return a 401;
			if(authValue != JWToken){
				cout << "Token mismatch\n";
				return crow::response(401);
			}
			else{
				cout << "Token match" << "\n";
			}
			crow::json::wvalue x;
			std::vector<string> m = read_messages(senderName, receiverName);
			for(int i = 0; i < m.size(); i++){
				x["Messages"][i] = m.at(i);
			}
			return crow::response(x);
			
			});


	CROW_ROUTE(app, "/user/<string>/send_messages").methods("POST"_method)([receiverName, &key](const crow::request& req, string senderName){
			string authValue = req.get_header_value("Authorization");
			//printf("%s\n",authValue);
			auto name = key.find(senderName);
			string JWToken = key.find(senderName) -> second;
			if(name == key.end()){
				cout << "Account not found\n";
				return crow::response(401);
			}
			else{
				cout << "Account found\n";
			}

			if(authValue != JWToken){
				cout << "Token mismatch\n";
				return crow::response(401);
			}
			else{
				cout << "Token found\n";
			}
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




	//a crow rout take a username and list/read all the messages for that user.
	//message_count
	//check_function
	app.port(18080).multithreaded().run();
	//cout << read_messages(senderName, recieverName);

}
