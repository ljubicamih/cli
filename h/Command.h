//
// Created by User on 31.01.2026..
//

#ifndef PROJEKAT_COMMAND_H
#define PROJEKAT_COMMAND_H


#pragma once
#include <string>

class Command
{
public:
    Command(std::istream& input, std::ostream& output); // prima ulazni i izlazni tok
    virtual void execute() = 0; // mora biti implementirana u izvedenim klasama
    std::ostream* getOutput();
    std::istream* getInput();
    void setOutput(std::ostream* output);
    void setInput(std::istream* input);
    virtual ~Command() = default;
protected:
    std::istream* input;
    std::ostream* output;

};

#endif //PROJEKAT_COMMAND_H
