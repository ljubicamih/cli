#ifndef PROJEKAT_BATCH_H
#define PROJEKAT_BATCH_H

#include <memory>
#include <string>
#include "Command.h"
#include "CommandContext.h"

class Interpreter;

class Batch : public Command{
public:
    Batch(std::istream& input, std::ostream& output, Interpreter& interpreter);
    void execute() override;

    static std::unique_ptr<Command> create(const CommandContext& ctx);

private:
    Interpreter& interpreter;
};

#endif