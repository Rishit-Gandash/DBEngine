#include "../src/create/create.h"
#include "../src/column/column.h"
#include "../src/helper/helper.h"
#include "create_test.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;


int test_create_database() {
    // Test 1: Simplest case
    std::string dbName = "testdb";
    fs::path fPath = filePath(dbName);
    if(create_database(dbName) == 0 && fs::exists(fPath)){
        std::cout << "SUCCESS: Test 1 passed\n";
        fs::remove_all(dirPath());
    } else {
        std::cout << "ERROR: Test 1 Failed\n";
        std::cout << "FilePath: " << fPath << "\n";
        std::cout << "DirPath: " << dirPath() << "\n";
        return -1;
    }

    // Test 2: DB directory already exists
    fs::create_directory(dirPath());
    dbName = "testdb";
    fPath = filePath(dbName);
    if(create_database(dbName) == 0 && fs::exists(fPath)){
        std::cout << "SUCCESS: Test 2 passed\n";
        fs::remove_all(dirPath());
    } else {
        std::cout << "ERROR: Test 2 Failed\n";
        std::cout << "FilePath: " << fPath << "\n";
        std::cout << "DirPath: " << dirPath() << "\n";
        return -1;
    }

    // Test 3: DB file already exists
    fs::create_directory(dirPath());
    fPath = filePath(dbName);
    std::ofstream dbFile(fPath); 
    dbName = "testdb";
    if(create_database(dbName) == -1){
        std::cout << "SUCCESS: Test 3 passed\n";
        fs::remove_all(dirPath());
    } else {
        std::cout << "ERROR: Test 3 Failed\n";
        std::cout << "FilePath: " << fPath << "\n";
        std::cout << "DirPath: " << dirPath() << "\n";
        return -1;
    }

    // Test 4: Checking if the content of .db are written properly
    dbName = "testdb";
    fPath = filePath(dbName);
    if(create_database(dbName) == 0 && fs::exists(fPath)){
        std::ifstream file(fPath);
        std::string line;
        if(std::getline(file, line) && line == "DATABASE NAME " + stringToUpper(dbName)){
            std::cout << "SUCCESS: Test 4 passed\n";
            fs::remove_all(dirPath());
        } else {
            std::cout << "ERROR: Test 4 Failed\n";
            std::cout << "FilePath: " << fPath << "\n";
            std::cout << "DirPath: " << dirPath() << "\n";
            return -1;
        }
    } else {
        std::cout << "ERROR: Test 4 Failed\n";
        std::cout << "FilePath: " << fPath << "\n";
        std::cout << "DirPath: " << dirPath() << "\n";
        return -1;
    }

    std::cout << "All create_database tests successful\n";
    return 0;
}


int test_create_table() {
    // Test 1: Simplest case - Creating a table in an existing database
    std::string dbName = "testdb";
    std::string tableName = "users";

    create_database(dbName);

    std::vector<Column> columns = {
        {"id", COLUMN_INT},
        {"name", COLUMN_STR}
    };

    fs::path fPath = filePath(dbName);

    if(create_table(dbName, tableName, columns) == 0 && fs::exists(fPath)){
        std::cout << "SUCCESS: Test 1 passed\n";
        fs::remove_all(dirPath());
    } else {
        std::cout << "ERROR: Test 1 Failed\n";
        std::cout << "FilePath: " << fPath << "\n";
        std::cout << "DirPath: " << dirPath() << "\n";
        return -1;
    }

    // Test 2: Checking if table content is written properly
    dbName = "testdb";
    tableName = "users";

    create_database(dbName);

    columns = {
        {"id", COLUMN_INT},
        {"name", COLUMN_STR}
    };

    fPath = filePath(dbName);

    if(create_table(dbName, tableName, columns) == 0 && fs::exists(fPath)){
        std::ifstream file(fPath);
        std::string line;
        std::vector<std::string> lines;

        while(std::getline(file, line)){
            lines.push_back(line);
        }

        if(lines.size() >= 5 &&
           lines[1] == "" &&
           lines[2] == "TABLE: USERS" &&
           lines[3] == "" &&
           lines[4] == "ROW 0 : id :: INT : name :: STR"){

            std::cout << "SUCCESS: Test 2 passed\n";
            // fs::remove_all(dirPath());
        } else {
            std::cout << "ERROR: Test 2 Failed\n";
            std::cout << "FilePath: " << fPath << "\n";
            std::cout << "DirPath: " << dirPath() << "\n";
            return -1;
        }
    } else {
        std::cout << "ERROR: Test 2 Failed\n";
        std::cout << "FilePath: " << fPath << "\n";
        std::cout << "DirPath: " << dirPath() << "\n";
        return -1;
    }

    std::cout << "All create_table tests successful\n";
    return 0;
}
