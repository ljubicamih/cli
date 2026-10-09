//
// Created by User on 23.02.2026...
//

#include "Translate.h"
#include <iostream>

Translate::Translate(std::istream& input, std::ostream& output, const std::string& what, const std::string& with) :
    Command(input, output), what(what), with(with) {}

Translate::Translate(std::istream &input, std::ostream& output, const std::string &what) :
    Command(input, output), what(what) {}


void Translate::execute() {
    std::string text;
    std::string result;
    while (std::getline(*input, text)) { //cita liniju po liniju
        int nextPosition = 0;

        while ((nextPosition = text.find(what, nextPosition)) != std::string::npos) { //trazenje svih pojavljivanja what u liniji
            text.replace(nextPosition, what.length(), with);
            nextPosition += what.length();
        }
        result += text + '\n';
    }
    if (!result.empty()) {
        result.pop_back(); // uklanjanje poslednjeg \n
    }
    *output << result;
    input->clear(); // resetovanje stanja ulaznog toka
}


std::unique_ptr<Command> Translate::create(const CommandContext& ctx) {
    return std::make_unique<Translate>(*ctx.input, *ctx.output, ctx.option, ctx.secondArgument);
}
