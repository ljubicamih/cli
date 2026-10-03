//
// Created by User on 01.02.2026..
//

#include "Touch.h"
#include "Exception.h"
#include <fstream>
#include <iostream>

Touch::Touch(std::istream& input, std::ostream& output, const std::string& filename)
    : Command(input, output), filename(filename) {

}

void Touch::execute() {
    if (filename==" ") {
        throw Exception("Greska! Morate uneti ime fajla!");
    }

    // provera da li fajl vec postoji
    std::ifstream in(filename);
    if (in.is_open()) {
        throw Exception("Greska! Fajl vec postoji!");
    }

    // kreiranje novog fajla
    std::ofstream out(filename);
    if (!out) {
        throw Exception("Greska! Fajl ne moze da se kreira!");
    }
    out.close();
}


std::unique_ptr<Command> Touch::create(const CommandContext& ctx) {
    if (ctx.quotedArgument) {
        throw Exception("Argument ne sme biti pod navodnicima");
    }
    if (ctx.argument.empty()) {
        throw Exception("Greska! Nije uneto ime fajla.");
    }
    return std::make_unique<Touch>(*ctx.input, *ctx.output, ctx.argument);
}
