#ifndef ECHO_H
#define ECHO_H

#include <memory>
#include <string>

#include "Command.h"
#include "CommandContext.h"

class Echo : public Command{
public:
    Echo(std::istream& input, std::ostream& output);

    void execute() override;
    static std::unique_ptr<Command> create(const CommandContext& ctx);

};

#endif