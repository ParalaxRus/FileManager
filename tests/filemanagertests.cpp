#include "filemanagertests.h"
#include "filemanager.h"
#include <functional>
#include <stdexcept>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace task {

namespace fs = boost::filesystem;

namespace {

struct TempPath final {
    fs::path src;
    explicit TempPath() {
        this->src = fs::current_path() / fs::unique_path();
        if (!fs::create_directories(this->src)) {
            throw std::runtime_error("Failed to create tmp path " + this->src.string());
        }
    }
    ~TempPath() {
        fs::remove_all(this->src);
    }
};

std::string readFile(fs::path src) {
    fs::ifstream input{src};
    std::ostringstream output;
    output << input.rdbuf();
    return output.str();
}

}

bool FileManagerTests::createNonExistingEmpty() {
    TempPath path;

    auto file = path.src / "a";
    FileManager::create(file.string());

    if (!fs::exists(file)) {
        return false;
    }

    auto data = readFile(file);
    return data.empty();
}

bool FileManagerTests::createNonExistingNonEmpty() {
    TempPath path;

    auto file = path.src / "a";
    FileManager::create(file.string(), "data");

    if (!fs::exists(file)) {
        return false;
    }

    auto data = readFile(file);
    return data == "data";
}

bool FileManagerTests::createExistingWithoutOverwrite() {
    TempPath path;

    auto file = path.src / "a";
    FileManager::create(file.string(), "data");
    try {
        FileManager::create(file.string(), "data1", false);
    }
    catch (const std::exception& ex) {
        return true;
    }

    return false;
}

bool FileManagerTests::createExistingWithOverwrite() {
    TempPath path;

    auto file = path.src / "a";
    FileManager::create(file.string(), "abc");
    FileManager::create(file.string(), "cba", true);
    
    auto data = readFile(file);
    return data == "cba";
}

bool FileManagerTests::copyNonExisting() {
    TempPath path;

    auto src = path.src / "a";
    auto dst = path.src / "b";

    try {
        FileManager::copy(src.string(), dst.string());
    }
    catch (const std::exception& ex) {
        return true;
    }

    return false;
}

bool FileManagerTests::copyExistingToExisting() {
    TempPath path;

    auto src = path.src / "a";
    FileManager::create(src.string(), "one");
    auto dst = path.src / "b";
    FileManager::create(dst.string(), "two");

    try {
        FileManager::copy(src.string(), dst.string());
    }
    catch (const std::exception& ex) {
        return true;
    }

    return false;
}

bool FileManagerTests::copyExistingToNonExisting() {
    TempPath path;

    auto src = path.src / "a";
    FileManager::create(src.string(), "one");
    auto dst = path.src / "b";

    FileManager::copy(src.string(), dst.string());

    auto data = readFile(dst);
    return data == "one";
}

bool FileManagerTests::copyExistingToExistingWithOverwrite() {
    TempPath path;

    auto src = path.src / "a";
    FileManager::create(src.string(), "one");
    auto dst = path.src / "b";
    FileManager::create(dst.string(), "two");

    FileManager::copy(src.string(), dst.string(), true);

    auto data = readFile(dst);
    return data == "one";
}

bool FileManagerTests::combineNonExistingFirst() {
    TempPath path;

    auto first = path.src / "a";
    auto second = path.src / "b";
    FileManager::create(second.string(), "2");
    auto dst = path.src / "c";

    try {
        FileManager::combine(first.string(), second.string(), dst.string());
    }
    catch (const std::exception& ex) {
        return true;
    }
    return false;
}

bool FileManagerTests::combineNonExistingSecond() {
    TempPath path;

    auto first = path.src / "a";
    FileManager::create(first.string(), "1");
    auto second = path.src / "b";
    auto dst = path.src / "c";

    try {
        FileManager::combine(first.string(), second.string(), dst.string());
    }
    catch (const std::exception& ex) {
        return true;
    }
    return false;
}

bool FileManagerTests::combineExistingFirstAndSecondToNonExistingDst() {
    TempPath path;

    auto first = path.src / "a";
    FileManager::create(first.string(), "1");
    auto second = path.src / "b";
    FileManager::create(second.string(), "2");
    auto dst = path.src / "c";

    FileManager::combine(first.string(), second.string(), dst.string());

    auto data = readFile(dst);
    return data == "12";
}

bool FileManagerTests::combineToExistingDst() {
    TempPath path;

    auto first = path.src / "a";
    FileManager::create(first.string(), "1");
    auto second = path.src / "b";
    FileManager::create(second.string(), "2");
    auto dst = path.src / "c";
    FileManager::create(dst.string(), "3");

    try {
        FileManager::combine(first.string(), second.string(), dst.string());
    }
    catch (const std::exception& ex) {
        return true;
    }
    return false;
}

bool FileManagerTests::combineToExistingDstAndOverwrite() {
    TempPath path;

    auto first = path.src / "a";
    FileManager::create(first.string(), "1");
    auto second = path.src / "b";
    FileManager::create(second.string(), "2");
    auto dst = path.src / "c";
    FileManager::create(dst.string(), "3");

    FileManager::combine(first.string(), second.string(), dst.string(), true);
    
    auto data = readFile(dst);
    return data == "12";
}

bool FileManagerTests::removeNonExisting() {
    TempPath path;

    auto file = path.src / "a";
    if (fs::exists(file)) {
        return false;
    }

    FileManager::remove(file.string());
    return !fs::exists(file);
}

bool FileManagerTests::removeExisting() {
    TempPath path;

    auto file = path.src / "a";
    FileManager::create(file.string(), "abc");
    if (!fs::exists(file)) {
        return false;
    }

    FileManager::remove(file.string());
    return !fs::exists(file);
}


void FileManagerTests::run() {
    using FuncDesc = std::pair<std::function<bool(void)>, std::string>;
    const std::vector<FuncDesc> testSuite = {
        // Create
        {&FileManagerTests::createNonExistingEmpty, "createNonExistingEmpty"},
        {&FileManagerTests::createNonExistingNonEmpty, "createNonExistingNonEmpty"},
        {&FileManagerTests::createExistingWithoutOverwrite, "createExistingWithoutOverwrite"},
        {&FileManagerTests::createExistingWithOverwrite, "createExistingWithOverwrite"},
        // Copy
        {&FileManagerTests::copyNonExisting, "copyNonExisting"},
        {&FileManagerTests::copyExistingToExisting, "copyExistingToExisting"},
        {&FileManagerTests::copyExistingToNonExisting, "copyExistingToNonExisting"},
        {&FileManagerTests::copyExistingToExistingWithOverwrite, "copyExistingToExistingWithOverwrite"},
        // Combine
        {&FileManagerTests::combineNonExistingFirst, "combineNonExistingFirst"},
        {&FileManagerTests::combineNonExistingSecond, "combineNonExistingSecond"},
        {&FileManagerTests::combineExistingFirstAndSecondToNonExistingDst, "combineExistingFirstAndSecondToNonExistingDst"},
        {&FileManagerTests::combineToExistingDst, "combineToExistingDst"},
        {&FileManagerTests::combineToExistingDstAndOverwrite, "combineToExistingDstAndOverwrite"},
        // Remove
        {&FileManagerTests::removeNonExisting, "removeNonExisting"},
        {&FileManagerTests::removeExisting, "removeExisting"},
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