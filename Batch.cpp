#include "Batch.h"
#include "Interpreter.h"
#include <fstream>
#include "Exception.h"

Batch::Batch(std::istream& input, std::ostream& output, Interpreter& interpreter)
    : Command(input, output), interpreter(interpreter)
{
}

void Batch::execute() {
    std::string line;
    while (std::getline(*input, line)) {
        if (line.empty())
            continue;
        interpreter.executeCommand(line,output);   //interpreter izvrsava komandu
    }
}


std::unique_ptr<Command> Batch::create(const CommandContext& ctx) {
    return std::make_unique<Batch>(*ctx.input, *ctx.output, *ctx.interpreter);
}