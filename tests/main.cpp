#include "create_test.h"
#include <iostream>


int main(){
    if(test_create_database() != 0) std::cout << "create_database test failed\n";
    return 0;
}
