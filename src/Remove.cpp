#include "Remove.h"
#include "Exception.h"
#include <filesystem>
#include <iostream>

Remove::Remove(std::istream& input, std::ostream& output, const std::string& filename)
    : Command(input, output), filename(filename)
{

}

void Remove::execute()
{
    if (!std::filesystem::remove(filename)) {
        throw Exception("Greska! Fajl ne postoji!");
    }
}


std::unique_ptr<Command> Remove::create(const CommandContext& ctx) {
    if (ctx.argument.empty()) {
        throw Exception("Greska! Nije uneto ime fajla.");
    }
    return std::make_unique<Remove>(*ctx.input, *ctx.output, ctx.argument);
}
