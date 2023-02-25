#include "command.h"
#include "filemanager.h"
#include <stdexcept>

namespace task {

const std::string CommandWithSource::srcKey = "src";
const std::string CreateCommand::textKey = "txt";
const std::string CopyCommand::dstKey = "dst";
const std::string CombineCommand::src2Key = "src2";

Command::Command(Operation op) : _operation(op) { }

std::string Command::find(const std::string& key) const {
    auto it = this->_args.find(key);
    if (it == this->_args.end()) {
        throw std::invalid_argument(key + " does not exist");
    }
    return it->second;
}

CommandWithSource::CommandWithSource(Operation op, const std::string& src) 
    : Command(op) { 
    this->_args[CommandWithSource::srcKey] = src;
}

std::string CommandWithSource::source() const {
    return this->find(CommandWithSource::srcKey);
}

CreateCommand::CreateCommand(const std::string& src, const std::string& text) 
    : CommandWithSource(Operation::create, src) { 
    this->_args[CreateCommand::textKey] = text;
}

std::string CreateCommand::text() const {
    return this->find(CreateCommand::textKey);
}


void CreateCommand::execute() {
    FileManager::create(this->source(), this->text());
}

CopyCommand::CopyCommand(Operation op, const std::string& src, const std::string& dst) 
    : CommandWithSource(Operation::copy, src) {
    this->_args[CopyCommand::dstKey] = dst;
}

CopyCommand::CopyCommand(const std::string& src, const std::string& dst) 
    : CopyCommand(Operation::copy, src, dst) {
}

void CopyCommand::execute() {
    FileManager::copy(this->source(), this->destination());
}

std::string CopyCommand::destination() const {
    return this->find(CopyCommand::dstKey);
}

CombineCommand::CombineCommand(const std::string& first, const std::string& second, const std::string& dst) 
    : CopyCommand(Operation::combine, first, dst) {
    this->_args[CombineCommand::src2Key] = second;
}

std::string CombineCommand::first() const {
    return this->source();
}

std::string CombineCommand::second() const {
    return this->find(CombineCommand::src2Key);
}

void CombineCommand::execute() {
    FileManager::combine(this->first(), this->second(), this->destination());
}

DeleteCommand::DeleteCommand(const std::string& src) : CommandWithSource(Operation::remove, src) {
}

void DeleteCommand::execute() {
    FileManager::remove(this->source());
}

}