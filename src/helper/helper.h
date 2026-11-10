#pragma once

#include<string>
#include<filesystem>
namespace fs = std::filesystem;

std::string stringToLower(std::string input);

std::string stringToUpper(std::string input);

fs::path filePath(std::string dbName);

fs::path dirPath();

bool lineStartsWith(std::string line, std::string prefix);
