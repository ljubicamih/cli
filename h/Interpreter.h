#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <iostream>
#include <vector>
#include "Parser.h"
#include "CommandContext.h"

class Interpreter
{
public:
    Interpreter() = default;

    void run();

    void executeCommand(const std::string& line, std::ostream* defaultOut=&std::cout);
    std::string rerunCapture(const std::string& line);

    void setPrompt(const std::string& newPrompt);
    void stop();

    bool isRunning() const;

private:
    bool running = true;       // status interpreter-a
    std::string prompt = "$ "; // trenutni prompt
    std::string lastCommandLine;
    void updateHistory(const std::string& line);
    void commandHandler(const CommandContext& ctx);


    std::vector<std::string> splitPipe(std::string line);

    std::istream* handleInput(const CommandContext& ctx);
    std::ostream* handleOutput(std::string parserOutput, Parser::RedirectType fileMode, std::ostream* defaultOut=&std::cout);
};

#endif // INTERPRETER_H