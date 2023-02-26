#pragma once

#include <string>
#include <thread>
#include <chrono>

namespace task {

class FileManager final {
private:
    static bool exists(const std::string& src);

    static bool createFile(const std::string& src, const std::string& text);

    static bool copyFile(const std::string& src, const std::string& dst);

    static bool combineFile(const std::string& first, 
                            const std::string& second, 
                            const std::string& dst);
                        
    static bool removeFile(const std::string& src);

    // Retry pattern in case if some files are locked
    template<class Fn, typename... Ts>
    static bool retry(Fn fn, int retryCount, int waitInMs, Ts... args) {
        for (int i = 0; i < retryCount; ++i) {
            if (fn(args ...)) {
                return true;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(waitInMs));
        }

        return false;
    }

public:
    FileManager() = delete;

    static void create(const std::string& src, 
                       const std::string& text = "", 
                       bool overwrite = false);

    static void copy(const std::string& src, 
                     const std::string& dst, 
                     bool overwrite = false);

    static void combine(const std::string& first, 
                        const std::string& second, 
                        const std::string& dst, 
                        bool overwrite = false);
                        
    static void remove(const std::string& src);
};

}