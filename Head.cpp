#include "Head.h"
#include "Exception.h"
#include <iostream>
#include <fstream>
#include <string>

Head::Head(std::istream& input, std::ostream& output, int n)
    : Command(input, output), n(n) {}

void Head::execute() {
    if (n<1 || n>10000) {
        throw Exception("Nevalidan unos n");
    }

    std::string text;
    std::string result;
    while (std::getline(*input, text)) { // cita liniju po liniju
        if (n-- > 0) {
            result += text + '\n';
        }
    }
    if (!result.empty()) {
        result.pop_back(); // uklanja poslednje \n
    }
    *output << result;
    input->clear(); // resetuje ulazni tok
}


std::unique_ptr<Command> Head::create(const CommandContext& ctx) {
    int numLines = 10;

    if (ctx.option.rfind("-n", 0) == 0) {
        try {
            numLines = std::stoi(ctx.option.substr(2));
        }
        catch (...) {
            throw Exception("Greska! Nevalidan broj linija.");
        }
    }

    return std::make_unique<Head>(*ctx.input, *ctx.output, numLines);
}

// UKLONJENO PRI REFAKTORISANJU - registracija je preseljena u
// registerAllCommands() (CommandRegistrations.cpp) - vidi Echo.cpp za puno
// objasnjenje.