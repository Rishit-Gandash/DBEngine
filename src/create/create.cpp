/*
DATABASE FILE: DATABASE NAME

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

#include <filesystem>
#include <fstream>
#include <string>
#include "../helper/helper.h"
#include <iostream>

namespace fs = std::filesystem;


// function expects you to provide the dbname formatted properly

int create_database(std::string dbName){
    fs::path curDir = fs::current_path() / "db";
    fs::path filePath = curDir / (stringToLower(dbName) + ".db");

    if(fs::exists(filePath)){
        std::cout << "Database already exists\n";
        return -1;
    }

    if(!fs::exists(curDir)){
        if(!fs::create_directory(curDir)){
            std::cout << "Could not create database directory\n";
            return -1;
        }
    }

    std::ofstream dbFile(filePath);

    if(dbFile.is_open()){
        dbFile << "DATABASE NAME " << stringToUpper(dbName) << "\n";
        dbFile.close();
        return 0;
    } else {
        std::cout << "Could not open database file\n";
        return -1;
    }
}
