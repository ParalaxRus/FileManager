#pragma once

#include <string>
#include <unordered_map>

namespace task {

class Command {
public:
    enum class Operation { undefined = -1, create, copy, combine, remove };

protected:
    Operation _operation = Operation::undefined;
    std::unordered_map<std::string, std::string> _args;

    std::string find(const std::string& key) const;
    explicit Command(Operation op);

public:
    Command() = delete;
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class CommandWithSource : public Command {
private:
    static const std::string srcKey;
protected:
    CommandWithSource(Operation op, const std::string& src);
public:
    CommandWithSource() = delete;
    std::string source() const;
};

class CreateCommand : public CommandWithSource {
private:
    static const std::string textKey;
public:
    explicit CreateCommand(const std::string& src, const std::string& text = "");
    std::string text() const;
    void execute() override;
    ~CreateCommand() override { }
};

class CopyCommand : public CommandWithSource {
private:
    static const std::string dstKey;
protected:
    CopyCommand(Operation op, const std::string& src, const std::string& dst);
public:
    CopyCommand(const std::string& src, const std::string& dst);
    std::string destination() const;
    void execute() override;
    ~CopyCommand() override { }
};

class CombineCommand : public CopyCommand {
private:
    static const std::string src2Key;
public:
    CombineCommand(const std::string& first, const std::string& second, const std::string& dst);
    std::string first() const;
    std::string second() const;
    void execute() override;
    ~CombineCommand() override { }
};

class DeleteCommand : public CommandWithSource {
public:
    explicit DeleteCommand(const std::string& src);
    void execute() override;
    ~DeleteCommand() override { }
};

}