//
// Created by User on 31.01.2026..
//

#ifndef PROJEKAT_DATE_H
#define PROJEKAT_DATE_H


#pragma once
#include <memory>

#include "Command.h"
#include "CommandContext.h"

class Date : public Command
{
public:
    Date(std::istream& input, std::ostream& output);
    void execute() override;
    static std::unique_ptr<Command> create(const CommandContext& ctx);
};

#endif //PROJEKAT_DATE_H