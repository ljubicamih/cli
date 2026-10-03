//
// Created by User on 16.02.2026..
//

#include "Interpreter.h"
#include "CommandRegistrations.h"

int main() {
    registerAllCommands();
    Interpreter interpreter;
    interpreter.run();
    return 0;
}
