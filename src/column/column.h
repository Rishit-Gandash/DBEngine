#pragma once 

#include <string>

typedef enum {
    COLUMN_INT,
    COLUMN_STR,
} ColumnType;

typedef struct {
    std::string ColumnName;
    ColumnType type;
} Column;

