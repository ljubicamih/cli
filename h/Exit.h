

#ifndef PROJEKAT_EXIT_H
#define PROJEKAT_EXIT_H

#include <memory>

#include "Command.h"
#include "CommandContext.h"

class Interpreter; // resava kruznu zavisnost

class Exit : public Command {
public:
    Exit(std::istream& input, std::ostream& output, Interpreter* interpreter);
    void execute() override;

    static std::unique_ptr<Command> create(const CommandContext& ctx);

private:
    Interpreter* interpreter;
};

#endif //PROJEKAT_EXIT_H
