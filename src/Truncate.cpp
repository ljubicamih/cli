//
// Created by User on 04.03.2026..
//

#include "Truncate.h"

#include "Command.h"
#include "Exception.h"
#include <fstream>

Truncate::Truncate(std::istream &input, std::ostream &output, const std::string &filename)
    : Command(input, output), filename(filename) {}

void Truncate::execute() {
    if (filename==" ") {
        throw Exception("Greska! Morate uneti ime fajla!");
    }

    // provera da li fajl vec postoji
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw Exception("Neuspesno otvaranje fajla");
    }
    file.close();
}


std::unique_ptr<Command> Truncate::create(const CommandContext& ctx) {
    return std::make_unique<Truncate>(*ctx.input, *ctx.output, ctx.argument);
}
