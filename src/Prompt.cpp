#include "Prompt.h"
#include "Interpreter.h"
#include "Exception.h"

Prompt::Prompt(std::istream& input, std::ostream& output, const std::string& newPrompt, Interpreter* interpreter)
    : Command(input, output), parameter(newPrompt), interpreter(interpreter)
{
}

void Prompt::execute()
{
    if (interpreter)
        interpreter->setPrompt(parameter);
}


std::unique_ptr<Command> Prompt::create(const CommandContext& ctx) {
    if (ctx.argument.empty()) {
        throw Exception("Greska! Prompt ne sme biti prazan.");
    }
    return std::make_unique<Prompt>(*ctx.input, *ctx.output, ctx.argument, ctx.interpreter);
}
