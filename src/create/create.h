#pragma once

#include "../column/column.h"
#include <string>
#include <vector>

int create_database(std::string dbName);

int create_table(std::string dbName, std::string tableName, std::vector<Column>& columns);
