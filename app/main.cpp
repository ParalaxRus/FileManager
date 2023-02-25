#include <iostream>
#include "parser.h"

int main(int argc, char **argv) {
    try {
        auto command = task::Parser::parse(argc, argv);
        command->execute();
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return -1;
    }
    
    std::cout << "Success" << std::endl;

    return 0;
}