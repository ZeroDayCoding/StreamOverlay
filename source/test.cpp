#include <iostream>

extern "C" void test() {
    #ifdef _DEBUG
        std::cout << "Hello from test using debug mode!" << std::endl;
    #else
        std::cout << "Hello from test using release mode!" << std::endl;
    #endif
}