//
// Created by User on 16.02.2026..
//

#ifndef PROJEKAT_REMOVE_H
#define PROJEKAT_REMOVE_H
#include "Command.h"
#include "CommandContext.h"
#include <memory>
#include <string>


class Remove : public Command {
public:
    explicit Remove(std::istream& input, std::ostream& output, const std::string& filename);
    void execute() override;
    static std::unique_ptr<Command> create(const CommandContext& ctx);
private:
    std::string filename;
};


#endif //PROJEKAT_REMOVE_H