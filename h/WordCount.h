//
// Created by User on 01.02.2026..
//

#ifndef PROJEKAT_WORDCOUNT_H
#define PROJEKAT_WORDCOUNT_H


#pragma once
#include "Command.h"
#include "CommandContext.h"
#include <memory>
#include <string>
#include <istream>

class WordCount : public Command {
public:
    WordCount(std::istream& input, std::ostream& output, const std::string& opt);
    void execute() override;
    static std::unique_ptr<Command> create(const CommandContext& ctx);
private:
    std::string option;
};


#endif //PROJEKAT_WORDCOUNT_H