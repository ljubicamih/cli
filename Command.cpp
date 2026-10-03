//
// Created by User on 31.01.2026..
//

#include "Command.h"

#include <ostream>

Command::Command(std::istream& input, std::ostream& output) : input(&input), output(&output) {
};

std::ostream *Command::getOutput() {
    return output;
}

std::istream *Command::getInput() {
    return input;
}

void Command::setOutput(std::ostream *output) {
    this->output = output;
}

void Command::setInput(std::istream *input) {
    this->input = input;
}
