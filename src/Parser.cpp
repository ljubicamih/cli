
#include "Parser.h"
#include "Exception.h"
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <sstream>

Parser::Parser(const std::string& line)
    : line(line),
      position(0),
      state(State::start),
      underQuotation(false),
    quotedArgument(false),
      error(false),
      errorPosition(0)
{
}

//getteri
std::string Parser::getCommand() { return commandName; }
std::string Parser::getArgument() { return argument; }
std::string Parser::getSecondArgument() { return secondArgument; }
Parser::RedirectType Parser::getFileMode() {
    return fileMode;
}
bool Parser::isQuoted() {
    return quotedArgument;
}
std::string Parser::getErrorMessage() { return errorMessage; }
int Parser::getErrorPosition() { return errorPosition; }
bool Parser::hasError() { return error; }
std::string Parser::getOption() { return option; }
std::string Parser::getOutput() {return output;}
char Parser::currentChar() {
    return (position < line.size()) ? line[position] : '\0';
}
void Parser::setError(const std::string& message) {
    throw Exception(message + "na poziciji " + std::to_string(position));
}

// preskace razmake dok ne naidje na karakter
void Parser::handleStart(char c) {
    if (std::isspace(c)) position++;
    else if (std::isalpha(c)) state = State::readCommand;
    else if (c == '\0') state = State::end;
    else setError("Neodgovarajuci pocetak komande");
}

// citanje komande
void Parser::handleReadCommand(char c) {
    if (std::isalpha(c)) {
        commandName += c;
        position++;
    }
    else if (std::isspace(c)) {
        state = State::afterCommand;
        position++;
    }
    else if (c == '\0') {
        state = State::end;
    }
    else {
        setError("Neodgovarajuci karakter u komandi");
    }
}

// nakon komande -> opcija ili argument
void Parser::handleAfterCommand(char c) {

    if (commandName == "tr") {
        processTr();
        state = State::end;
    }
    else {
        if (std::isspace(c)) {
            position++;
        }
        else if (c == '-') {
            state = State::readOption;
            position++;
        }
        else if (c == '"') {
            underQuotation = true;
            quotedArgument = true;
            state = State::readQuotedArgument;

            position++;
        }
        else if (c == '\0') {
            state = State::end;
        }
        else if (c=='>') {
            state = State::readOutput;
            position++;
        }
        else {
            state = State::readArgument;
        }
    }
}

// citanje opcije
void Parser::handleReadOption(char c) {
    if (option.empty()) option += '-';
    if (std::isalnum(c) or c=='.' or c=='-') {
        option += c;
        position++;
    }
    else if (c == '"') {
        if (!underQuotation) {
            underQuotation = true;
        }
        else {
            underQuotation = false;
            state = State::afterCommand;
        }
        position++;
    }
    else if (std::isspace(c)) {
        state = State::afterCommand;
        position++;
    }
    else if (c == '\0') state = State::end;
    else setError("Neodgovarajuca opcija");
}

// nakon opcije -> argument ili navodnici
void Parser::handleAfterOption(char c) {
    if (std::isspace(c)) position++;
    else if (c == '"') {
        underQuotation = true;
        state = State::readQuotedArgument;
        position++;
    }
    else if (c == '\0') state = State::end;
    else state = State::readArgument;
}

// argument bez navodnika
void Parser::handleReadArgument(char c) {
    if (c == '\0') {
        state = State::end;
    }
    else if (std::isspace(c) && commandName!="tr"){
        state = State::readOutput;
        position++;
    }
    else {
        argument += c;
        position++;
    }
}

// argument u navodnicima
void Parser::handleReadQuotedArgument(char c) {
    if (c == '"' && underQuotation) {
        underQuotation = false;
        position++;
        state = State::readOutput;
    }
    else if (c == '\0') {
        setError("Fali navodnik za zatvaranje ");
    }
    else {
        argument += c;  // dodaj sve znakove između navodnika
        position++;
    }
}

//redirekcija
void Parser::handleOutput(char c) {
    if (c=='>') {
        position++;
        fileMode = RedirectType::Append;
    }
    else if (c=='\0') {
        state = State::end;
    }
    else if (isspace(c)) {
        position++;
    }
    else {
        output += c;
        position++;
    }
}

void Parser::processTr() {
    std::istringstream stream(line);
    std::string token;
    int endFirstArgument = 0;
    int endOption = 0;
    stream >> token;
    if (!(stream >> token)) {
        throw Exception("Fali -\"what\"");
    }
    if (token[0]=='-') {
        endOption = parseOption(stream,token, endFirstArgument);
    }
    else {
        parseFirstArgument(stream, token);
    }
    if (!(stream>>token)) {
        if (option.empty()) {
            throw Exception("Fali -\"what\"");
        }
        return;
    }
    if (token[0]=='-') {
        if (option.empty()) {
            endOption = parseOption(stream, token, endFirstArgument);
        }
        else {
            throw Exception("Dupli -\"what\"");
        }
    }
    else {
        if (option.empty()) {
            throw Exception("Nije uneta opcija");
        }
        parseSecondArgument(stream, token, endOption);
    }
    if (!(stream>>token)) { //opcioni drugi argument ili redirekcija
        return;
    }
    if (token[0] == '"') {
        if (secondArgument.empty()) {
            parseSecondArgument(stream,token, endOption);
        }
        else {
            throw Exception("Previse argumenata");
        }
    }
    else if (token[0] == '>') {
        parseOutput(token);
    }
    else {
        throw Exception("Neispravan format");
    }
    if (!(stream>>token)) { //potencijalna dodatna redirekcija
        return;
    }
    if (token[0]=='>') {
        parseOutput(token);
    }
    else {
        throw Exception("Neispravna redirekcija izlaza");
    }
}

int Parser::parseFirstArgument(std::istringstream& stream, std::string& token) { //prvi argument(string ili fajl)
    if (token[0] == '"') {
        int startArg = line.find("\"");
        int endArg = line.find("\"", startArg + 1);

        argument = line.substr(startArg + 1, endArg - startArg - 1);
        quotedArgument = true;
        token.erase(0,1);

        while (token.find("\"") == std::string::npos)
            stream >> token;
        return endArg + 1;
    }
    if (token[0] == '<')
        token.erase(0,1);
    argument = token;
    return 0;
}

int Parser::parseOption(std::istringstream& stream, std::string& token, int endFirstArgument) { //-what
    int startOpt = line.find("\"",endFirstArgument);
    int endOpt = line.find("\"", startOpt + 1);

    option = line.substr(startOpt + 1, endOpt - startOpt - 1);
    token.erase(0,2);

    while (token.find("\"") == std::string::npos)
        stream >> token;
    return endOpt+1;
}

void Parser::parseSecondArgument(std::istringstream& stream, std::string& token, int endOption) { //with
    int startSecondArg = line.find("\"",endOption);
    int endSecondArg = line.find("\"", startSecondArg + 1);
    secondArgument = line.substr(startSecondArg + 1, endSecondArg - startSecondArg - 1);

    token.erase(0,1);

    while (token.find("\"") == std::string::npos)
        stream >> token;
}

void Parser::parseOutput(std::string& token) { //izlazna redirekcija
    token.erase(0,1);

    if (token[0] == '>') {
        token.erase(0,1);
        fileMode = RedirectType::Append;
    }

    output = token;
}

void Parser::parse() {
    state = State::start;
    position = 0;
    commandName.clear();
    option.clear();
    argument.clear();
    error = false;

    while (state != State::end && state != State::error) {
        char c = currentChar();

        switch (state) {
        case State::start: handleStart(c); break;
        case State::readCommand: handleReadCommand(c); break;
        case State::afterCommand: handleAfterCommand(c); break;
        case State::readOption: handleReadOption(c); break;
        case State::afterOption: handleAfterOption(c); break;
        case State::readArgument: handleReadArgument(c); break;
        case State::readQuotedArgument: handleReadQuotedArgument(c); break;
        case State::readOutput: handleOutput(c); break;
        default: break;
        }
    }
}
