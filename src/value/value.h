#pragma once

#include <string>
#include <variant>
typedef enum {
    VALUE_INT,
    VALUE_STR
} ValueType;

typedef struct {
    ValueType type;
    std::variant<int, std::string> data;
} Value;
