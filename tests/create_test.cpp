#include "../src/create/create.h"
#include "../src/helper/helper.h"
#include "create_test.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

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
