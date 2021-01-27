#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<sqlite3.h>
#include<string>

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
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
		return (0);
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
		fprintf(stdout, "Data successfully added to the table");
	}

	sqlite3_close(db);
}
//delete from USERS then
//delete from sqlite_sequence where name = 'your_table_name'