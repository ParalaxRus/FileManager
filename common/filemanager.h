#pragma once

#include <string>

namespace task {

class FileManager final {
private:
    static bool exists(const std::string& src);

public:
    FileManager() = delete;

    static void create(const std::string& src, const std::string& text = "", bool overwrite = false);
    static void copy(const std::string& src, const std::string& dst, bool overwrite = false);
    static void combine(const std::string& first, const std::string& second, const std::string& dst, bool overwrite = false);
    static void remove(const std::string& src);
};

}