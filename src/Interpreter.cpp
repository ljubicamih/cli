#include "Interpreter.h"

#include "Parser.h"
#include "Exception.h"
#include "Command.h"
#include "CommandContext.h"
#include "CommandRegistry.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>


namespace {
    std::string trimmed(const std::string& s) {
        size_t start = s.find_first_not_of(" \t");
        if (start == std::string::npos) {
            return "";
        }
        size_t end = s.find_last_not_of(" \t");
        return s.substr(start, end - start + 1);
    }
}

void Interpreter::run()
{
    while (running)
    {
        std::cout << prompt;

        std::string line;
        if (!std::getline(std::cin, line))
            break;
        executeCommand(line);
        updateHistory(line);
    }
}

bool Interpreter::isRunning() const
{
    return running;
}

void Interpreter::setPrompt(const std::string& newPrompt)
{
    prompt = newPrompt + " ";
}

void Interpreter::stop()
{
    running = false;
}

//izvrsavanje komande
void Interpreter::executeCommand(const std::string& line, std::ostream* defaultOut)
{
    std::vector<std::string> commandsString = splitPipe(line);
    try
    {
        std::istream* prevOutput = nullptr;
        for (size_t i = 0; i < commandsString.size(); ++i) {
            Parser parser(commandsString[i]);
            parser.parse();
            CommandContext ctx;
            ctx.command = parser.getCommand();
            ctx.argument = parser.getArgument();
            ctx.quotedArgument = parser.isQuoted();
            ctx.option = parser.getOption();
            ctx.secondArgument = parser.getSecondArgument();
            ctx.interpreter = this;
            ctx.previousCommand = (i == 0) ? trimmed(lastCommandLine) : trimmed(commandsString[i-1]);

            std::istream* commandInput = (i == 0) ? &std::cin : prevOutput;
            std::ostream* commandOutput = defaultOut;
            std::stringstream *buffer = nullptr;
            if (i!=0 and !ctx.argument.empty()) throw Exception("input nije dozvoljan u cevovodu");
            if (i!=commandsString.size()-1 && !parser.getOutput().empty()) throw Exception("output nije dozvoljen u cevovodu");
            if (!ctx.argument.empty()) {
                commandInput = handleInput(ctx);
            }
            if (i<commandsString.size()-1) {
                buffer = new std::stringstream();
                commandOutput = buffer;
            }
            else if (!parser.getOutput().empty()) {
                commandOutput = handleOutput(parser.getOutput(),parser.getFileMode(),defaultOut);
            }

            ctx.input = commandInput;
            ctx.output = commandOutput;

            commandHandler(ctx);

            if (buffer) {
                prevOutput = buffer;
            }
            std::cout << std::endl;
        }
    }
    catch (const Exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void Interpreter::commandHandler(const CommandContext& ctx) {
    if (ctx.command.empty())
        return;

    std::unique_ptr<Command> command = CommandRegistry::instance().create(ctx.command, ctx);
    command->execute();
    ctx.output->flush();
}

//citanje unosa
std::istream* Interpreter::handleInput(const CommandContext& ctx) {
    if (!CommandRegistry::instance().treatsArgumentAsStream(ctx.command)) {
        return &std::cin;
    }

    std::istream *input;
    if (ctx.quotedArgument) {
        input = new std::istringstream(ctx.argument);
    }
    else if (!ctx.argument.empty()) {
        std::string argument = ctx.argument;
        if (argument[0] == '<') {
            argument.erase(0,1);
        }
        input = new std::ifstream(argument);
        if (!dynamic_cast<std::ifstream*>(input)->is_open()) {
            throw Exception("Nije moguce otvoriti fajl");
        }
    }
    else {
        input = &std::cin;
    }
    return input;
}

std::ostream* Interpreter::handleOutput(std::string parserOutput, Parser::RedirectType fileMode, std::ostream* defaultOut) {
    std::ostream *output;
    if (!parserOutput.empty()) {
        if (fileMode == Parser::RedirectType::Append) {
            output = new std::ofstream(parserOutput,std::ios_base::app);
        }
        else {
            output = new std::ofstream(parserOutput);
        }
        if (!dynamic_cast<std::ofstream*>(output)->is_open()) {
            throw Exception("Neuspesno otvaranje redirekcionog fajla");
        }
    }
    else {
        output = defaultOut;
    }
    return output;
}

std::vector<std::string> Interpreter::splitPipe(std::string line) {
    bool inQuotes = false;
    std::vector<std::string> result;
    std::string current = "";
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == '\"') {
            inQuotes = !inQuotes;
            current += line[i];
        }
        else if (line[i] == '|' and !inQuotes) {
            result.push_back(current);
            current = "";
        }
        else
            current += line[i];
    }
    result.push_back(current);
    return result;
}

// ============================================================

void Interpreter::updateHistory(const std::string& line) {
    std::vector<std::string> stages = splitPipe(line);
    if (stages.empty()) {
        return;
    }
    try {
        Parser parser(stages[0]);
        parser.parse();
        if (parser.getCommand().empty() || parser.getCommand() == "last") {
            return;
        }
    }
    catch (const Exception&) {
        return;
    }
    lastCommandLine = line;
}

std::string Interpreter::rerunCapture(const std::string& line) {
    Parser parser(line);
    parser.parse();

    CommandContext ctx;
    ctx.command = parser.getCommand();
    ctx.argument = parser.getArgument();
    ctx.quotedArgument = parser.isQuoted();
    ctx.option = parser.getOption();
    ctx.secondArgument = parser.getSecondArgument();
    ctx.interpreter = this;

    std::ostringstream capture;
    try {
        ctx.input = ctx.argument.empty() ? &std::cin : handleInput(ctx);
        ctx.output = &capture;
        commandHandler(ctx);
    }
    catch (const Exception& e) {
        capture << e.what() << std::endl;
    }
    return capture.str();
}