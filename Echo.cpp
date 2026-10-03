#include "Echo.h"
#include <iostream>
#include <fstream>
#include <sstream>

Echo::Echo(std::istream& input, std::ostream& output)
    : Command(input,output) { }

void Echo::execute() {

    std::string text;
    std::string result;
    while (std::getline(*input, text)) { //cita liniju po liniju
        result += text + '\n';
    }
    if (!result.empty()) {
        result.pop_back(); // brise poslednje \n
    }
    *output << result;
    input->clear(); // resetovanje ulaznog toka
}


std::unique_ptr<Command> Echo::create(const CommandContext& ctx) {
    return std::make_unique<Echo>(*ctx.input, *ctx.output);
}
