

#include "Last.h"
#include "Exception.h"
#include "Interpreter.h"

#include <iostream>

Last::Last(std::istream& input, std::ostream& output, const std::string& previousCommand, Interpreter& interpreter)
    : Command(input, output), previousCommand(previousCommand), interpreter(interpreter)
{
}

void Last::execute() {
    *output << previousCommand << std::endl;
    *output << interpreter.rerunCapture(previousCommand);
}


std::unique_ptr<Command> Last::create(const CommandContext& ctx) {
    if (!ctx.argument.empty()) {
        throw Exception("Funkcija ne treba da prima argument");
    }
    if (ctx.previousCommand.empty()) {
        throw Exception("Nema prethodne komande");
    }
    return std::make_unique<Last>(*ctx.input, *ctx.output, ctx.previousCommand, *ctx.interpreter);
}
