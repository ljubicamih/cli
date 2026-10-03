//
// Created by User on 01.02.2026..
//

#ifndef PROJEKAT_PARSER_H
#define PROJEKAT_PARSER_H

#include <string>

class Parser {
public:

    enum class RedirectType { Overwrite, Append };
    explicit Parser(const std::string& line);

    void parse();

    std::string getCommand();
    std::string getArgument();
    std::string getSecondArgument();
    bool isQuoted();
    std::string getOption();
    std::string getErrorMessage();
    std::string getOutput();
    RedirectType getFileMode();

    int getErrorPosition();
    bool hasError();
    // Parser.h (dodaj ove dve metode ako već nisu tu)
    std::string getWhat() const { return what; }
    std::string getWith() const { return with; }

private:
    std::string line;
    int position;

    enum class State {
        start,
        readCommand,
        afterCommand,
        readOption,
        afterOption,
        readArgument,
        readQuotedArgument,
        readOutput,
        end,
        error
    } state;

    bool underQuotation;
    bool quotedArgument;

    bool readingArgument;
    bool readingWhat;
    bool readingWith;

    std::string commandName;
    std::string option;
    std::string argument;
    std::string secondArgument;
    std::string what;
    std::string with;
    std::string output;
    RedirectType fileMode = RedirectType::Overwrite;

    bool error;
    std::string errorMessage;
    int errorPosition;

    char currentChar();
    void setError(const std::string& message);

    void handleStart(char c);
    void handleReadCommand(char c);
    void handleAfterCommand(char c);
    void handleReadOption(char c);
    void handleAfterOption(char c);
    void handleReadArgument(char c);
    void handleReadQuotedArgument(char c);
    void handleOutput(char c);
    void processTr();
    int parseFirstArgument(std::istringstream& stream, std::string& token);
    int parseOption(std::istringstream& stream, std::string& token, int endFirstArgument);
    void parseSecondArgument(std::istringstream& stream, std::string& token, int option);
    void parseOutput(std::string& token);
};

#endif // PROJEKAT_PARSER_H