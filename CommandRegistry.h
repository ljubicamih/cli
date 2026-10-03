//
// ============================================================
// NOVI FAJL - CEO OVAJ FAJL JE DODAT PRI REFAKTORISANJU
// ============================================================
//

#ifndef PROJEKAT_COMMANDREGISTRY_H
#define PROJEKAT_COMMANDREGISTRY_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "CommandContext.h"

class Command;

using CommandFactory = std::function<std::unique_ptr<Command>(const CommandContext&)>;

class CommandRegistry {
public:
    static CommandRegistry& instance();
    void registerCommand(const std::string& name, CommandFactory factory, bool treatArgumentAsStream = true);

    bool contains(const std::string& name) const;
    bool treatsArgumentAsStream(const std::string& name) const;
    // ako komanda sa datim imenom nije registrovana.
    std::unique_ptr<Command> create(const std::string& name, const CommandContext& ctx) const;

private:
    CommandRegistry() = default;

    struct Entry {
        CommandFactory factory;
        bool treatArgumentAsStream;
    };

    std::unordered_map<std::string, Entry> entries;
};

#endif //PROJEKAT_COMMANDREGISTRY_H
