

#ifndef PROJEKAT_LAST_H
#define PROJEKAT_LAST_H

#include <memory>
#include <string>

#include "Command.h"
#include "CommandContext.h"

class Interpreter;

class Last : public Command {
public:
    Last(std::istream& input, std::ostream& output, const std::string& previousCommand, Interpreter& interpreter);
    void execute() override;
    static std::unique_ptr<Command> create(const CommandContext& ctx);

private:
    std::string previousCommand;
    Interpreter& interpreter;
};

#endif //PROJEKAT_LAST_H
