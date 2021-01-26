#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<sqlite3.h>

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}



int data() {
	sqlite3* db; //This is the database object
	char* errMsg = 0;
	int rc; //Variable used to open and create your database file
	const char* sql; //Variable used to create you sql tables

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
	sql = "CREATE TABLE USERS(" \
		"ID	INTEGER	PRIMARY KEY	AUTOINCREMENT,"	\
		"Username	TEXT	NOT NULL,"	\
		"First_Name	TEXT	NOT NULL,"	\
		"Last_Name	TEXT	NOT NULL,"	\
		"Password	TEXT	NOT	NULL);";

	//Execute SQL statement
	rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", errMsg);
	}
	else {
		fprintf(stdout, "Table successfully created");
	}

	sqlite3_close(db);
}