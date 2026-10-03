

#include "Exit.h"
#include "Interpreter.h"

Exit::Exit(std::istream& input, std::ostream& output, Interpreter* interpreter)
    : Command(input, output), interpreter(interpreter)
{
}

void Exit::execute()
{
    if (interpreter)
        interpreter->stop();
}

std::unique_ptr<Command> Exit::create(const CommandContext& ctx) {
    return std::make_unique<Exit>(*ctx.input, *ctx.output, ctx.interpreter);
}
