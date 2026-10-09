//
// Created by User on 24.02.2026..
//

#ifndef PROJEKAT_HEAD_H
#define PROJEKAT_HEAD_H

#include "Command.h"
#include "CommandContext.h"  // DODATO PRI REFAKTORISANJU
#include <memory>  // DODATO PRI REFAKTORISANJU
#include <string>

class Head : public Command {
public:
    Head(std::istream& input, std::ostream& output, int n);
    void execute() override;

    static std::unique_ptr<Command> create(const CommandContext& ctx);
private:
    int n; //broj linija koje treba da ispise
};


#endif //PROJEKAT_HEAD_H