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
			string keyPub = R"(AAAAB3NzaC1yc2EAAAADAQABAAABgQDRpv/FkkTkkc3dGrfUK8zOHRsH+r35fFadn+MR3w/T1PDHDg+1P+s8LcQdZDPZP7nbv0hbB58xh2TmjgJF0m+DHdyLMlYG9FTV+aVCYpZysReTFDwug2gUblBPtPHiga5IlfctOewVjv8COptTzLmaeLXFUOmmsDKuTRvTexa6KYW7rhTvVi/uL1tz1Pmte8B+baAgyZLfAn61LwQrWKaDzKTAhcIS79Hyyi07Y1yP/QQf+CTe1NcqLXxQDuGc/2JHTPudRwCT7Gf3gFGF+ATdx0yF3ju1JrToTCKfsMIv2tE6i4ZxS9tp4o157dXPR/14lJr3Ac+mLtR2mL/WW+V/GUR1xhuc6Ysit2V0mlbhsOfEMUyzjsKs+tBlYYwwKpxM7VR9+RxFJjD8GphdailOfa2T8Q2isuJiv5pXmgbzmMAiCgwRRyzylDVYbFsMz8f1MpkMJ411Etc47OH3C4YUTdgWoQ24XCem146Y69xiDklE2f1Cx3iMm5y4OUjBe7s=)";

			string keyPrivate = R"(b3BlbnNzaC1rZXktdjEAAAAABG5vbmUAAAAEbm9uZQAAAAAAAAABAAABlwAAAAdzc2gtcn
NhAAAAAwEAAQAAAYEA0ab/xZJE5JHN3Rq31CvMzh0bB/q9+XxWnZ/jEd8P09Twxw4PtT/r
PC3EHWQz2T+5279IWwefMYdk5o4CRdJvgx3cizJWBvRU1fmlQmKWcrEXkxQ8LoNoFG5QT7
Tx4oGuSJX3LTnsFY7/AjqbU8y5mni1xVDpprAyrk0b03sWuimFu64U71Yv7i9bc9T5rXvA
fm2gIMmS3wJ+tS8EK1img8ykwIXCEu/R8sotO2Ncj/0EH/gk3tTXKi18UA7hnP9iR0z7nU
cAk+xn94BRhfgE3cdMhd47tSa06Ewin7DCL9rROouGcUvbaeKNee3Vz0f9eJSa9wHPpi7U
dpi/1lvlfxlEdcYbnOmLIrdldJpW4bDnxDFMs47CrPrQZWGMMCqcTO1UffkcRSYw/BqYXW
opTn2tk/ENorLiYr+aV5oG85jAIgoMEUcs8pQ1WGxbDM/H9TKZDCeNdRLXOOzh9wuGFE3Y
FqENuFwnpteOmOvcYg5JRNn9Qsd4jJucuDlIwXu7AAAFmHSixLp0osS6AAAAB3NzaC1yc2
EAAAGBANGm/8WSROSRzd0at9QrzM4dGwf6vfl8Vp2f4xHfD9PU8McOD7U/6zwtxB1kM9k/
udu/SFsHnzGHZOaOAkXSb4Md3IsyVgb0VNX5pUJilnKxF5MUPC6DaBRuUE+08eKBrkiV9y
057BWO/wI6m1PMuZp4tcVQ6aawMq5NG9N7FrophbuuFO9WL+4vW3PU+a17wH5toCDJkt8C
frUvBCtYpoPMpMCFwhLv0fLKLTtjXI/9BB/4JN7U1yotfFAO4Zz/YkdM+51HAJPsZ/eAUY
X4BN3HTIXeO7UmtOhMIp+wwi/a0TqLhnFL22nijXnt1c9H/XiUmvcBz6Yu1HaYv9Zb5X8Z
RHXGG5zpiyK3ZXSaVuGw58QxTLOOwqz60GVhjDAqnEztVH35HEUmMPwamF1qKU59rZPxDa
Ky4mK/mleaBvOYwCIKDBFHLPKUNVhsWwzPx/UymQwnjXUS1zjs4fcLhhRN2BahDbhcJ6bX
jpjr3GIOSUTZ/ULHeIybnLg5SMF7uwAAAAMBAAEAAAGBAMcVNwJNIGCQWBWi3nd61DPRja
6pGydDPBjYEE8TK7tzFOVg4+ewd9egef+S/G1LR1l1rebLOQ9WS6lnpp7Y8o1mmNwRg4F9
GOZL9vMwHT9yDTncWD2vCPGFw3u9DoiRroc86QgoXZgnPt7F+mO8H2+hOrLRX96qqKW9kT
PkSbOj5FtRNo4DoOYkUEqRLjrgLe2gehNIdtCQVPQGXoYu24iCltw+6AkFdK+B7yva8bXF
hNo60ABNyrhBky+Owg1MsDWVCNh8wcI5tLFZGxo6IHxVAzQQzfOsxQHGhxcdtq6y9zC3ko
gJKVM2Wh6fq5HL0V6/NxciZo36KsP2UStzKDVf+sQDFr7nXrv7PxcC24xIU6tmjtcdugSh
REuc3cuHtucF66h4iU+wrstHOzAftr+JpksWX0mgEyeYhU9qPlLoxYLZwzqajfVyH5sfVM
mRSpYyU2r8BBcBbt5T8NACWtYGOg67GPak21todwaOxoAhcw5fNCC2M8KRd9upTGE3iQAA
AMBUinOMp33bP/IlDMcwJiBtWj5v/Xi4zmV8CqoIGYvtjNEcXiVK8KxEvdRfr+e+xXtjzQ
XePoU3whM55GK7jfyt9/xnkFcUCGNNAQtIr3RoDKAD2g4LQnQN7H7FF9jdhFICo2SYcmbI
UER2UozHJc+CQYdU7kHsr7cc5mSYBX0tgZs25PTN6RsGA17wHsfES0TB4din9+pI9r3tAs
1jAIdXM3z+fxBr/jY14wQsOwkihH53gi7YzBvj8OhV68MGyFUAAADBAOnYGuKR4MD21hv9
JV2H7R2t+d+1ex3ShnOUea7mkNxBhlvPxZ4sErB/ikHZvhTt0nMYa25NzBez8T63OH8LYJ
9HzjEZdNcQ25Th5N+W1ABYRpYxrxKdl3OSPNorXJjRXAb7xuKQKUi2FKK+6/mKrCW1E3Wt
n1WVmbcXNsT4a7bN7VGMZnCnb0fydN85TazGCVYo+3lgsWc99luN+pQ+J+tmO7X50wWBaN
pYZOF12x6B0vvrJRf1PTqGZyvkaMaRDQAAAMEA5YQe+Ujqbx707bUiVEquVpNTOo932U2v
/GntIO6IZqZzxcoobkbtZ0K3LgR+Q9rjqTPxm1kVqsUs90TMAG4u9L0zuiV1ugtK3EzsUd
Kk0RCxDydr+qxYFutMOzwi9f3bqAMKkD/ArArTCHK4RuKTGZ6MtpHgCqIpUoWngjpqFGNs
SQA8dEbFLH4ue1FzsUXIFaYQhIRyFYzy7roG8xjydwJGUl/X9iyAqHiFmOoU3Yx5P1W/W9
EOspHjy2NK9r3nAAAAHW1hcmVpY0BtYXJlaWMtVmlydHVhbC1NYWNoaW5lAQIDBAU=)";

			auto token = jwt::create().set_type("JWT").sign(jwt::algorithm::rs256(keyPub, keyPrivate,"",""));
			crow::response success = crow::response(200);
			success.add_header("type", token);

			return success;
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
