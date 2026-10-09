//
// Created by User on 01.02.2026..
//

#ifndef PROJEKAT_TOUCH_H
#define PROJEKAT_TOUCH_H


#pragma once
#include "Command.h"
#include "CommandContext.h"
#include <memory>
#include <string>

class Touch : public Command
{
public:
    explicit Touch(std::istream& input, std::ostream& output, const std::string& filename);
    void execute() override;
    static std::unique_ptr<Command> create(const CommandContext& ctx);
private:
    std::string filename;
};


#endif //PROJEKAT_TOUCH_H