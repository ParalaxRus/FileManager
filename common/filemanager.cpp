#include "filemanager.h"
#include <fstream>
#include <stdexcept>
#include <cstdio>

namespace task {

bool FileManager::exists(const std::string& src) {
    std::ifstream input(src);
    return input.good();
}

void FileManager::create(const std::string& src, const std::string& text, bool overwrite) {
    if (!overwrite && FileManager::exists(src)) {
        throw std::invalid_argument(src + " already exists");
    }

    std::ofstream output(src);
    output << text;
}

void FileManager::copy(const std::string& src, const std::string& dst, bool overwrite) {
    if (!FileManager::exists(src)) {
        throw std::invalid_argument(src + " does not exist");
    }

    if (!overwrite && FileManager::exists(dst)) {
        throw std::invalid_argument(dst + " already exists");
    }

    std::ifstream input(src, std::ios::binary);
    std::ofstream output(dst, std::ios::binary);

    output << input.rdbuf();
}

void FileManager::combine(const std::string& first, const std::string& second, const std::string& dst, bool overwrite) {
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

    std::ofstream output(dst.c_str(), output.in | output.binary | output.ate);
    std::ifstream input(second.c_str());
    output << input.rdbuf();
}

void FileManager::remove(const std::string& src) {
    if (!FileManager::exists(src)) {
        return;
    }

    if (std::remove(src.c_str()) != 0) {
        throw std::runtime_error("Failed to delete " + src);
    }
}

}