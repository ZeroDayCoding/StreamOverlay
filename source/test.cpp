#include "platform.h"
#include <iostream>

extern "C" void test() {
    #ifdef _DEBUG
        std::cout << "Hello from test using debug mode!" << std::endl;
    #else
        std::cout << "Hello from test using release mode!" << std::endl;
    #endif
    __COMPILE_LINE_FOR_LINUX(std::cout << "Using Linux!" << std::endl);
    __COMPILE_LINE_FOR_WINDOWS(std::cout << "Using Windows!" << std::endl);
}