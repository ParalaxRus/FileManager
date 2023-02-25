#include <iostream>
#include "commandtests.h"
#include "filemanagertests.h"

int main(int argc, char **argv) {
    try {
        task::CommandTests::run();
        task::FileManagerTests::run();
        std::cout << "Tests passed" << std::endl;
        
        return 0;
    }
    catch (const std::exception& ex) {
        std::cout << "Tests failed: " << ex.what() << std::endl;

        return -1;
    }
}