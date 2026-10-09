//
// Created by User on 23.02.2026..
//

#ifndef PROJEKAT_TRANSLATE_H
#define PROJEKAT_TRANSLATE_H
#include "Command.h"
#include "CommandContext.h"
#include <memory>
#include <string>
#include <istream>


class Translate : public Command {
public:
    Translate(std::istream& input, std::ostream& output, const std::string& what, const std::string& with);
    Translate(std::istream& input, std::ostream& output, const std::string& what);
    void execute() override;
    static std::unique_ptr<Command> create(const CommandContext& ctx);
private:
    std::string what;
    std::string with;
};


#endif //PROJEKAT_TRANSLATE_H