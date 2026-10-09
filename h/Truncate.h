//
// Created by User on 04.03.2026..
//

#ifndef PROJEKAT_TRUNCATE_H
#define PROJEKAT_TRUNCATE_H
#include <memory>
#include <string>
#include "Command.h"
#include "CommandContext.h"


class Truncate : public Command{
public:
    Truncate(std::istream& input, std::ostream& output, const std::string& filename);
    void execute() override;

    static std::unique_ptr<Command> create(const CommandContext& ctx);
private:
    std::string filename;
};


#endif //PROJEKAT_TRUNCATE_H