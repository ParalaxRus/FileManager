#pragma once

namespace task {

// TO-DO: locked files cases are not tested yet
class FileManagerTests final {
private:
    static bool createNonExistingEmpty();
    static bool createNonExistingNonEmpty();
    static bool createExistingWithoutOverwrite();
    static bool createExistingWithOverwrite();
    static bool copyNonExisting();
    static bool copyExistingToExisting();
    static bool copyExistingToNonExisting();
    static bool copyExistingToExistingWithOverwrite();
    static bool combineNonExistingFirst();
    static bool combineNonExistingSecond();
    static bool combineExistingFirstAndSecondToNonExistingDst();
    static bool combineToExistingDst();
    static bool combineToExistingDstAndOverwrite();
    static bool removeNonExisting();
    static bool removeExisting();

public:
    FileManagerTests() = delete;
    static void run();
};

}