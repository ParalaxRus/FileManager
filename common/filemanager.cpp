#include "filemanager.h"
#include <fstream>
#include <stdexcept>
#include <cstdio>

namespace task {

namespace {
    const int kRetryCount = 3;
    const int kRetryWaitMs = 5;
}

bool FileManager::exists(const std::string& src) {
    std::ifstream input(src);
    return input.good();
}

bool FileManager::createFile(const std::string& src, const std::string& text) {
    std::ofstream output(src);
    output << text;
    return output.good();
}

bool FileManager::copyFile(const std::string& src, const std::string& dst) {
    std::ifstream input(src, std::ios::binary);
    std::ofstream output(dst, std::ios::binary);

    output << input.rdbuf();

    return output.good();
}

bool FileManager::combineFile(const std::string& first, 
                              const std::string& second, 
                              const std::string& dst) {
    std::ofstream output(dst.c_str(), output.in | output.binary | output.ate);
    std::ifstream input(second.c_str());
    output << input.rdbuf();

    return output.good();
}
                 
bool FileManager::removeFile(const std::string& src) {
     return (std::remove(src.c_str()) == 0);
}

void FileManager::create(const std::string& src, const std::string& text, bool overwrite) {
    if (!overwrite && FileManager::exists(src)) {
        throw std::invalid_argument(src + " already exists");
    }

    if (!FileManager::retry(FileManager::createFile, kRetryCount, kRetryWaitMs, src, text)) {
        throw std::invalid_argument("Create failed");
    }
}

void FileManager::copy(const std::string& src, const std::string& dst, bool overwrite) {
    if (!FileManager::exists(src)) {
        throw std::invalid_argument(src + " does not exist");
    }

    if (!overwrite && FileManager::exists(dst)) {
        throw std::invalid_argument(dst + " already exists");
    }

    if (!FileManager::retry(FileManager::copyFile, kRetryCount, kRetryWaitMs, src, dst)) {
        throw std::invalid_argument("Create failed");
    }
}

void FileManager::combine(const std::string& first, 
                          const std::string& second, 
                          const std::string& dst, 
                          bool overwrite) {
    if (!FileManager::exists(first)) {
        throw std::invalid_argument(first + " does not exist");
    }

    if (!FileManager::exists(second)) {
        throw std::invalid_argument(second + " does not exist");
    }

    if (!overwrite && FileManager::exists(dst)) {
        throw std::invalid_argument(dst + " already exists");
    }

    if (overwrite) {
        FileManager::remove(dst);
    }

    FileManager::copy(first, dst);

    if (!FileManager::retry(FileManager::combineFile, kRetryCount, kRetryWaitMs, first, second, dst)) {
        throw std::invalid_argument("Create failed");
    }
}

void FileManager::remove(const std::string& src) {
    if (!FileManager::exists(src)) {
        return;
    }

    if (!FileManager::retry(FileManager::removeFile, kRetryCount, kRetryWaitMs, src)) {
        throw std::invalid_argument("Create failed");
    }
}

}