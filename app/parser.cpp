#include "parser.h"
#include <boost/program_options.hpp>

namespace task {

namespace po = boost::program_options;

std::unique_ptr<Command> Parser::parse(int argc, char **argv) {
    const std::string kCreate = "create";
    const std::string kCopy = "copy";
    const std::string kCombine = "combine";
    const std::string kDelete = "delete";

    po::options_description desc("Allowed options");
    desc.add_options()
        (kCreate.c_str(), po::value<std::vector<std::string>>()->multitoken(), "Create file [src] [data]")
        (kCopy.c_str(), po::value<std::vector<std::string>>()->multitoken(), "Copy file [src] [dst]")
        (kCombine.c_str(), po::value<std::vector<std::string>>()->multitoken(), "Combine file [first] [second] [dst]")
        (kDelete.c_str(), po::value<std::string>(), "Delete file [src]");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count(kCreate)) {
        auto params = vm[kCreate].as<std::vector<std::string>>();
        if ((params.size() < 0) || (params.size() > 2)) {
            throw std::invalid_argument("Invalid command");    
        }
        auto src = params[0];
        auto dst = params.size() == 2 ? params[1] : "";
        return std::make_unique<CreateCommand>(src, dst);
    }
    else if (vm.count(kCopy)) {
        auto params = vm[kCopy].as<std::vector<std::string>>();
        if (params.size() != 2) {
            throw std::invalid_argument("Invalid command");    
        }
        return std::make_unique<CopyCommand>(params[0], params[1]);
    }
    else if (vm.count(kCombine)) {
        auto params = vm[kCombine].as<std::vector<std::string>>();
        if (params.size() != 3) {
            throw std::invalid_argument("Invalid command");    
        }
        return std::make_unique<CombineCommand>(params[0], params[1], params[2]);
    }
    else if (vm.count(kDelete)) {
        auto params = vm[kDelete].as<std::string>();
        return std::make_unique<DeleteCommand>(params);
    }
    else {
        const std::string usage = "filemanager [command] [args]\ncommand:\ncreate src [data]\ncopy src dst\ncombine first second dst\ndelete src\nexample: <filemanager --create tmp.txt text>";
        throw std::invalid_argument("Invalid command. Usage: \n" + usage);
    }

    return 0;
}

}