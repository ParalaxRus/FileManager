#pragma once

namespace task {

class CommandTests final {
private:
    static bool createCommand();
    static bool createCommandWithoutText();
    static bool copyCommand();
    static bool combineCommand();
    static bool deleteCommand();

public:
    CommandTests() = delete;
    static void run();
};

}