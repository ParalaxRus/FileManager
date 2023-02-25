#pragma once

#include <memory>
#include "command.h"

namespace task {

class Parser final {
public:
    Parser() = delete;

    // Parses input arguments if any and produces command
    // Supports one command at a time for now
    // Next step: add support for a collections of commands
    static std::unique_ptr<Command> parse(int argc, char **argv);
};

}