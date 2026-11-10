/*

DATABASE NAME TESTDB
    TABLE: TABLE_NAME

    ROW 0: COLUMN 1: COLUMN 2: ... 
    ROW 1: COLUMN_1_DATA : COLUMN_2_DATA : ..

Create functions: 

You can create a database, creation of a database just means that a file is created with atleast the db info line
    - For now it just creates a database directory and writes the db file in it
    - the header line is just "DATABASE FILE"

You can create a table, you must specify the columns in a strict format, expression evaluation will not be handled here
Perhaps it may be useful to mangle an id column here


The data in columns can be ints or strings

You can create a row, you must specify info for each column

*/

#include "../helper/helper.h"
#include "../column/column.h"
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;


// function expects you to provide the dbname formatted properly

int create_database(std::string dbName){
    fs::path curDir = fs::current_path() / "db";
    fs::path dbFilePath = curDir / (stringToLower(dbName) + ".db");

    if(fs::exists(dbFilePath)){
        std::cout << "Database already exists\n";
        return -1;
    }

    if(!fs::exists(curDir)){
        if(!fs::create_directory(curDir)){
            std::cout << "Could not create database directory\n";
            return -1;
        }
    }

    std::ofstream dbFile(dbFilePath);

    if(dbFile.is_open()){
        dbFile << "DATABASE NAME " << stringToUpper(dbName) << "\n";
        dbFile.close();
        return 0;
    } else {
        std::cout << "Could not open database file\n";
        return -1;
    }
}


/*
 * This function expects a database name, table name, and a column array 
 * which it writes to the .db file 
 */

int create_table(std::string dbName, std::string tableName, std::vector<Column>& columns){
    fs::path dbFilePath = filePath(dbName);

    if(!fs::exists(dbFilePath)){
        std::cout << "database does not exist\n";
        return -1;
    }

    std::fstream dbFile(dbFilePath, std::ios::in | std::ios::out | std::ios::app);

    if(dbFile.is_open()){
        std::string firstline;
        if(!(std::getline(dbFile, firstline) && firstline == "DATABASE NAME " + stringToUpper(dbName))){
            std::cout << "invalid database name\n";
            return -1;
        }
        dbFile.seekp(0, std::ios::end);
        dbFile << "\n";
        dbFile << "TABLE: " << stringToUpper(tableName) << "\n";
        dbFile << "\n";
        dbFile << "ROW 0";
        for(const Column& column: columns){
            dbFile << " : ";
            dbFile << column.ColumnName << " :: ";
            if(column.type == COLUMN_INT){
                dbFile << "INT";
            } else if (column.type == COLUMN_STR){
                dbFile << "STR";
            }
        }
        dbFile << "\n";
        dbFile.close();
        return 0;
    } else {
        std::cout << "Could not open database file\n";
        return -1;
    }
}
