//
// Created by User on 01.02.2026..
//

#ifndef PROJEKAT_TIME_H
#define PROJEKAT_TIME_H


#pragma once
#include <memory>
#include <string>

#include "Command.h"
#include "CommandContext.h"

class Time : public Command
{
public:
    Time(std::istream& input, std::ostream& output);
    void execute() override;
    static std::unique_ptr<Command> create(const CommandContext& ctx);
};



#endif //PROJEKAT_TIME_H