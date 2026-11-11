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
            fs::remove_all(dirPath());
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
    
    // Test 3 Multiple Tables
    dbName = "testdb";
    std::string tableName1 = "users";
    std::string tableName2 = "teachers";

    create_database(dbName);

    std::vector<Column> columns1 = {
        {"id", COLUMN_INT},
        {"name", COLUMN_STR}
    };

    std::vector<Column> columns2 = {
        {"id", COLUMN_INT},
        {"name", COLUMN_STR},
        {"age", COLUMN_INT}
    };

    fPath = filePath(dbName);
    int t1 = create_table(dbName, tableName1, columns1);
    int t2 = create_table(dbName, tableName2, columns2);

    if(t1 == 0 && t2 == 0 && fs::exists(fPath)){
        std::cout << "SUCCESS: Test 3 passed\n";
        fs::remove_all(dirPath());
    } else {
        std::cout << "ERROR: Test 3 Failed\n";
        std::cout << "FilePath: " << fPath << "\n";
        std::cout << "DirPath: " << dirPath() << "\n";
        return -1;
    }

    std::cout << "All create_table tests successful\n";
    return 0;
}

int test_create_row() {
    // Test 1: Simplest case - Creating a row in an existing table
    std::string dbName = "testdb";
    std::string tableName = "users";

    create_database(dbName);

    std::vector<Column> columns = {
        {"id", COLUMN_INT},
        {"name", COLUMN_STR}
    };

    create_table(dbName, tableName, columns);

    std::vector<Value> values = {
        {VALUE_INT, 1},
        {VALUE_STR, "John"}
    };

    fs::path fPath = filePath(dbName);

    if(create_row(dbName, tableName, values) == 0 && fs::exists(fPath)){
        std::cout << "SUCCESS: Test 1 passed\n";
        fs::remove_all(dirPath());
    } else {
        std::cout << "ERROR: Test 1 Failed\n";
        std::cout << "FilePath: " << fPath << "\n";
        std::cout << "DirPath: " << dirPath() << "\n";
        return -1;
    }

    // Test 2: Checking if row content is written properly
    dbName = "testdb";
    tableName = "users";

    create_database(dbName);

    columns = {
        {"id", COLUMN_INT},
        {"name", COLUMN_STR}
    };

    create_table(dbName, tableName, columns);

    values = {
        {VALUE_INT,  1},
        {VALUE_STR, "John"}
    };

    fPath = filePath(dbName);

    if(create_row(dbName, tableName, values) == 0 && fs::exists(fPath)){
        std::ifstream file(fPath);
        std::string line;
        std::vector<std::string> lines;

        while(std::getline(file, line)){
            lines.push_back(line);
        }

        if(lines.size() >= 6 &&
           lines[2] == "TABLE: USERS" &&
           lines[4] == "ROW 0 : id :: INT : name :: STR" &&
           lines[5] == "ROW : 1 : John"){

            std::cout << "SUCCESS: Test 2 passed\n";
            fs::remove_all(dirPath());
        } else {
            std::cout << "ERROR: Test 2 Failed\n";

            for(const std::string& l : lines){
                std::cout << l << "\n";
            }

            return -1;
        }
    } else {
        std::cout << "ERROR: Test 2 Failed\n";
        return -1;
    }

    // Test 3: Checking multiple row insertions
    dbName = "testdb";
    tableName = "users";

    create_database(dbName);

    columns = {
        {"id", COLUMN_INT},
        {"name", COLUMN_STR}
    };

    create_table(dbName, tableName, columns);

    values = {
        {VALUE_INT, 1},
        {VALUE_STR, "John"}
    };

    fPath = filePath(dbName);

    bool success = (create_row(dbName, tableName, values) == 0);

    values = {
        {VALUE_INT, 2},
        {VALUE_STR, "Alice"}
    };

    success = success && (create_row(dbName, tableName, values) == 0);

    values = {
        {VALUE_INT, 3},
        {VALUE_STR, "Bob"}
    };

    success = success && (create_row(dbName, tableName, values) == 0);

    if(success && fs::exists(fPath)){
        std::ifstream file(fPath);
        std::string line;
        std::vector<std::string> lines;

        while(std::getline(file, line)){
            lines.push_back(line);
        }

        if(
           lines[2] == "TABLE: USERS" &&
           lines[4] == "ROW 0 : id :: INT : name :: STR" &&
           lines[5] == "ROW : 1 : John" &&
           lines[6] == "ROW : 2 : Alice" &&
           lines[7] == "ROW : 3 : Bob"){

            std::cout << "SUCCESS: Test 3 passed\n";
            fs::remove_all(dirPath());
        } else {
            std::cout << "ERROR: Test 3 Failed at matching\n";

            for(const std::string& l : lines){
                std::cout << l << "\n";
            }

            return -1;
        }
    } else {
        std::cout << "ERROR: Test 3 Failed\n";
        return -1;
    }


    std::cout << "All create_row tests successful\n";
    return 0;
}
