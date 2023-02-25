#include "commandtests.h"
#include "command.h"
#include <functional>
#include <stdexcept>

namespace task {

bool CommandTests::createCommand() {
    CreateCommand command("a", "v");
    return ((command.source() == "a") && (command.text() == "v"));
}

bool CommandTests::createCommandWithoutText() {
    CreateCommand command("a");
    return ( (command.source() == "a") && command.text().empty() );
}

bool CommandTests::copyCommand() {
    CopyCommand command("a", "b");
    return ((command.source() == "a") && (command.destination() == "b"));
}

bool CommandTests::combineCommand() {
    CombineCommand command("a", "b", "c");
    return ( (command.source() == command.first()) && 
             (command.first() == "a") && 
             (command.second() == "b") && 
             (command.destination() == "c"));
}

bool CommandTests::deleteCommand() {
    DeleteCommand command("a");
    return (command.source() == "a");
}

void CommandTests::run() {
    using FuncDesc = std::pair<std::function<bool(void)>, std::string>;
    const std::vector<FuncDesc> testSuite = {
        {&CommandTests::createCommand, "createCommand"},
        {&CommandTests::createCommandWithoutText, "createCommandWithoutText"},
        {&CommandTests::copyCommand, "copyCommand"},
        {&CommandTests::combineCommand, "combineCommand"},
        {&CommandTests::deleteCommand, "deleteCommand"},
    };

    for (const auto& test : testSuite) {
        try {
            if (!test.first()) {
                throw std::runtime_error(test.second);
            }
        }
        catch (const std::exception& ex) {
            throw std::runtime_error(test.second + " " + ex.what());
        }
    }
}

}