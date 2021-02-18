#include "crow_all.h"
#include "sqliteDatabase.h"
#include <iostream>
using namespace std;



int main(int argc, char* argv[]){
	crow::SimpleApp app;
	
	CROW_ROUTE(app, "/")
	([](){
		return "<div><h1>Hello, Crow.</h1><div>";
	});

	CROW_ROUTE(app, "/page1")
	([](){
		return "<div><p>This is page one.</p><div>";
	});
	
	char* port = getenv("PORT");
	uint16_t iPort = static_cast<uint16_t>(port != NULL? stoi(port): 18080);
	cout << "PORT =" << iPort << "\n";
	app.port(iPort).multithreaded().run();
}
	
