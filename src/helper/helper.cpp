#include <algorithm>
#include<filesystem>
#include <string>

namespace fs = std::filesystem;

std::string stringToLower(std::string input){
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

std::string stringToUpper(std::string input){
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    return input;
}

fs::path filePath(std::string dbName){
    return fs::current_path() / "db" / (dbName + ".db");
}

fs::path dirPath(){
    return fs::current_path() / "db";
}

bool lineStartsWith(std::string line, std::string prefix) {
    return line.rfind(prefix, 0) == 0;
}
