

#include "CommandRegistry.h"
#include "Command.h"
#include "Exception.h"

CommandRegistry& CommandRegistry::instance() {
    static CommandRegistry registry;
    return registry;
}

void CommandRegistry::registerCommand(const std::string& name, CommandFactory factory, bool treatArgumentAsStream) {
    entries[name] = Entry{std::move(factory), treatArgumentAsStream};
}

bool CommandRegistry::contains(const std::string& name) const {
    return entries.find(name) != entries.end();
}

bool CommandRegistry::treatsArgumentAsStream(const std::string& name) const {
    auto it = entries.find(name);
    if (it == entries.end())
        return true; // podrazumevano ponasanje - isto kao i ranije za nepoznatu komandu
    return it->second.treatArgumentAsStream;
}

std::unique_ptr<Command> CommandRegistry::create(const std::string& name, const CommandContext& ctx) const {
    auto it = entries.find(name);
    if (it == entries.end())
        throw Exception("Nepoznata komanda: " + name);
    return it->second.factory(ctx);
}
