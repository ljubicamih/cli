

#ifndef PROJEKAT_COMMANDCONTEXT_H
#define PROJEKAT_COMMANDCONTEXT_H

#include <istream>
#include <ostream>
#include <string>

class Interpreter; // izbegava kruzna zavisnost sa Interpreter.h

struct CommandContext {
    std::string command;         // ime komande (npr. "echo")
    std::string argument;        // prvi argument (ili "" ako ga nema)
    bool quotedArgument = false; // da li je argument bio pod navodnicima
    std::string option;          // opcija (npr. "-w", "-n5", ili kod tr celo "-what")
    std::string secondArgument;  // drugi argument (kod tr: "with")

    std::string previousCommand;

    std::istream* input = nullptr;
    std::ostream* output = nullptr;

    Interpreter* interpreter = nullptr; // za komande koje uticu na sam interpreter (prompt, batch, exit)
};

#endif //PROJEKAT_COMMANDCONTEXT_H
