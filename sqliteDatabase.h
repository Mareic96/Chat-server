#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<sqlite3.h>
#include<string>
#include<vector>

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}


int users_table() {
	sqlite3* db; //This is the database object
	char* errMsg = 0;
	int rc; //Variable used to open and create your database file
	std::string sql; //Variable used to create you sql tables
	sqlite3_stmt* stmt = 0;

	rc = sqlite3_open("User Information.db", &db);

	//Checks if the file has been created and if not, it creates one 
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stderr, "Opended database successfully\n");
	}
	
	//creat table if it doesn't exist
	sql = "CREATE TABLE IF NOT EXISTS USERS("\
		"ID	INTEGER	PRIMARY KEY	AUTOINCREMENT,"	\
		"Username	TEXT	NOT NULL,"	\
		"First_Name	TEXT	NOT NULL,"	\
		"Last_Name	TEXT	NOT NULL,"	\
		"Password	TEXT	NOT	NULL);";


	//Execute SQL statement
	rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}

int data(std::string username, std::string firstName, std::string lastName, std::string password) {
	sqlite3* db; //This is the database object
	char* errMsg = 0;
	int rc; //Variable used to open and create your database file
	std::string sql; //Variable used to create you sql tables
	sqlite3_stmt* stmt = 0;

	rc = sqlite3_open("User Information.db", &db);

	//Checks if the file has been created and if not, it creates one 
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stderr, "Opended database successfully\n");
	}

	//Create the table
	/*sql = "CREATE TABLE USERS(" \
		"ID	INTEGER	PRIMARY KEY	AUTOINCREMENT,"	\
		"Username	TEXT	NOT NULL,"	\
		"First_Name	TEXT	NOT NULL,"	\
		"Last_Name	TEXT	NOT NULL,"	\
		"Password	TEXT	NOT	NULL);";*/

	//Adding user records

	sql = "INSERT INTO USERS(Username, First_Name, Last_name, Password)"	\
		"VALUES(?, ?, ?, ?);";

	//Execute SQL statement
	//rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);

	rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, username.c_str(), username.length(), NULL);
	sqlite3_bind_text(stmt, 2, firstName.c_str(), firstName.length(), NULL);
	sqlite3_bind_text(stmt, 3, lastName.c_str(), lastName.length(), NULL);
	sqlite3_bind_text(stmt, 4, password.c_str(), password.length(), NULL);
	rc = sqlite3_step(stmt);

	if (rc != SQLITE_DONE) {
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stdout, "Data successfully added to the table\n");
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
//delete from USERS then
//delete from sqlite_sequence where name = 'your_table_name'

//create table if not exists 'name of table';

bool login_check(std::string username, std::string password) {
	sqlite3* db;
	char* errMsg = 0;
	int rc;
	std::string sql;
	sqlite3_stmt* stmt = 0;
	bool authentication = false;
	rc = sqlite3_open("User Information.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return (0);
	}
	else {
		fprintf(stderr, "Opended database successfully\n");
	}

	//checking user details
	sql = "SELECT * from USERS where Username = ? and Password = ?";
	int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, username.c_str(), username.length(), NULL);
	sqlite3_bind_text(stmt, 2, password.c_str(), password.length(), NULL);

	if (result == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			fprintf(stdout, "User account found\n");
			fprintf(stdout, "Hello %s\n", sqlite3_column_text(stmt, 2));
			authentication = true;
		}
		else {
			fprintf(stdout, "User account not found. Username or password do not match, please try again\n");
		}
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return authentication;

}

bool check(std::string reciever) {
	sqlite3* db;
	char errMsg = 0;
	std::string sql;
	int rc = 0;
	sqlite3_stmt* stmt = 0;
	bool match = false;

	rc = sqlite3_open("User Information.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return (0);
	}
	else {
		fprintf(stderr, "Opended database successfully\n");
	}

	//check whether the reciever's username exists
	sql = "SELECT * FROM USERS WHERE Username = ?";
	int result = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, reciever.c_str(), reciever.length(), NULL);
	
	if (result == SQLITE_OK) {
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			fprintf(stdout, " %s found!\n", sqlite3_column_text(stmt, 2));
			match = true;
		}
	}
	else {
		fprintf(stdout, "Username is not found. Please try again");
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return match;
}

int message_table() {
	sqlite3* db; //This is the database object
	char* errMsg = 0;
	int rc; //Variable used to open and create your database file
	std::string sql; //Variable used to create you sql tables

	rc = sqlite3_open("Messages.db", &db);

	//Checks if the file has been created and if not, it creates one 
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stderr, "Opended database successfully\n");
	}

	//creat table if it doesn't exist
	sql = "CREATE TABLE IF NOT EXISTS MESSAGES("	\
		"ID	INTEGER	PRIMARY KEY	NOT NULL, "	\
		"Sender		TEXT	NOT NULL,"	\
		"Reciever	TEXT	NOT NULL,"	\
		"Content	TEXT	NOT NULL);";

	rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);


	//Execute SQL statement
	rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stdout, "Table created successfully\n");
	}

	sqlite3_close(db);
	return 0;
}

int message_table_edit() {
	sqlite3* db;
	char* errMsg = 0;
	std::string sql;
	int rc = 0;

	rc = sqlite3_open("Messages.db", &db);
	if (rc) {
		fprintf(stderr, "Database failed to open %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stdout, "Database opended successfully\n");
	}

	sql = "alter table Messages add Receipt TEXT";
	sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stdout, "Column added\n");
	}

	sqlite3_close(db);
	return 0;

}

int store_message(std::string sender, std::string reciever, std::string content) {
	sqlite3* db;
	char* errMsg = 0;
	int rc;
	std::string sql;
	sqlite3_stmt* stmt = 0;

	rc = sqlite3_open("Messages.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stdout, "Opended database successfully created\n");
	}

	/*sql = "CREATE TABLE MESSAGES("	\
		"ID	INTEGER	PRIMARY KEY	NOT NULL, "	\
		"Sender		TEXT	NOT NULL,"	\
		"Reciever	TEXT	NOT NULL,"	\
		"Content	TEXT	NOT NULL);";*/

	//rc = sqlite3_exec(db, sql.c_str(), callback, 0, &errMsg);

	sql = "INSERT INTO MESSAGES(Sender, Reciever, Content)"	\
		"VALUES(?, ?, ?);";
	

	rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, sender.c_str(), sender.length(), NULL);
	sqlite3_bind_text(stmt, 2, reciever.c_str(), reciever.length(), NULL);
	sqlite3_bind_text(stmt, 3, content.c_str(), content.length(), NULL);
	rc = sqlite3_step(stmt);
	
	

	if (rc != SQLITE_DONE) {
		fprintf(stderr, "SQL error (%d): %s\n", rc, sqlite3_errmsg(db));
	}
	else {
		fprintf(stdout, "Message sent\n");
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}

/*string read_messages(std::string sender, std::string reciever) {
	sqlite3* db;
	char* errMsg = 0;
	int rc;
	std::string sql;
	sqlite3_stmt* stmt = 0;
	std::string m;

	rc = sqlite3_open("Messages.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stdout, "Database opened\n");
	}

	sql = "SELECT * FROM MESSAGES WHERE Sender = ? and Reciever = ?";

	rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, sender.c_str(), sender.length(), NULL);
	sqlite3_bind_text(stmt, 2, reciever.c_str(), reciever.length(), NULL);
	//rc = sqlite3_step(stmt);
	
	if (rc == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {

			m = std::string(reinterpret_cast <char*>(const_cast <unsigned char*> (sqlite3_column_text(stmt, 3))));
			fprintf(stdout,"%s\n", m.c_str());
		}
	}
	else {
		fprintf(stderr, "fail%d\n", rc);
		fprintf(stderr, "%s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return m;
}*/

std::vector<std::string> read_messages(std::string sender, std::string reciever) {
	sqlite3* db;
	char* errMsg = 0;
	int rc;
	std::string sql;
	sqlite3_stmt* stmt = 0;
	std::string a;
	std::vector<std::string> m;

	rc = sqlite3_open("Messages.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stdout, "Database opened\n");
	}

	sql = "SELECT * FROM MESSAGES WHERE Sender = ? and Reciever = ?";

	rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, sender.c_str(), sender.length(), NULL);
	sqlite3_bind_text(stmt, 2, reciever.c_str(), reciever.length(), NULL);
	//rc = sqlite3_step(stmt);
	
	if (rc == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {

			a = std::string(reinterpret_cast <char*>(const_cast <unsigned char*> (sqlite3_column_text(stmt, 3))));
			m.push_back(a);
			//fprintf(stdout,"%s\n", a.c_str());
		}
	}
	else {
		fprintf(stderr, "fail%d\n", rc);
		fprintf(stderr, "%s\n", sqlite3_errmsg(db));
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return m;
}

int read_receipt(std::string receiver) {
	sqlite3* db;
	char* errMsg = 0;
	std::string sql;
	std::string read = "Read";
	int rc;
	sqlite3_stmt* stmt = 0;


	rc = sqlite3_open("Messages.db", &db);
	if (rc) {
		fprintf(stderr, "Unable to open databse %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stdout, "Database opened successfully\n");
	}

	sql = "UPDATE Messages SET Receipt = ? where Reciever = ?"; //Ask about the read text, need preparaed statment?

	rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, read.c_str(), read.length(), NULL);
	sqlite3_bind_text(stmt, 2, receiver.c_str(), receiver.length(), NULL);

	
	if (rc == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			std::string r = std::string(reinterpret_cast <char*>(const_cast <unsigned char*>(sqlite3_column_text(stmt, 4))));
		}
	}
	else {
		fprintf(stderr, "SQL error %d (%s)\n", rc, sqlite3_errmsg(db));
	}


	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return 0;
}


int message_count(std::string sender) {
	sqlite3* db;
	char* errMsg = 0;
	std::string sql;
	int rc;
	sqlite3_stmt* stmt = 0;
	int rowcount = 0;
	
	rc = sqlite3_open("Messages.db", &db);
	if (rc) {
		fprintf(stderr, "Unable to open databse %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stdout, "Database opened successfully\n");
	}

	sql = "SELECT COUNT ('Content') FROM MESSAGES where Reciever = ?";

	rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, sender.c_str(), sender.length(), NULL);
	rc = sqlite3_step(stmt);


	if (rc == SQLITE_ROW) {
		rowcount = sqlite3_column_int(stmt, 0);
		fprintf(stdout, "You have %d message(s)\n", rowcount);
	}
	else {
		fprintf(stderr, "SQL error %d (%s)\n", rc, sqlite3_errmsg(db));
	}


	sqlite3_finalize(stmt);
	sqlite3_close(db);
	
	return rowcount;
}


//alter table MESSAGES add Receipt TEXT;
//update Messages set Receipt = 'Read';
//Maybe write a vector which returns all messages
