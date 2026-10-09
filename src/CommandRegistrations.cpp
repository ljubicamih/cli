

#include "CommandRegistry.h"

#include "Echo.h"
#include "Date.h"
#include "Time.h"
#include "Touch.h"
#include "Remove.h"
#include "Truncate.h"
#include "WordCount.h"
#include "Head.h"
#include "Translate.h"
#include "Batch.h"
#include "Prompt.h"
#include "Exit.h"
#include "Last.h"

void registerAllCommands() {
    CommandRegistry::instance().registerCommand("echo", Echo::create);
    CommandRegistry::instance().registerCommand("date", Date::create);
    CommandRegistry::instance().registerCommand("time", Time::create);
    CommandRegistry::instance().registerCommand("touch", Touch::create, false);
    CommandRegistry::instance().registerCommand("rm", Remove::create, false);
    CommandRegistry::instance().registerCommand("truncate", Truncate::create, false);
    CommandRegistry::instance().registerCommand("wc", WordCount::create);
    CommandRegistry::instance().registerCommand("head", Head::create);
    CommandRegistry::instance().registerCommand("tr", Translate::create);
    CommandRegistry::instance().registerCommand("batch", Batch::create);
    CommandRegistry::instance().registerCommand("prompt", Prompt::create);
    CommandRegistry::instance().registerCommand("exit", Exit::create);
    CommandRegistry::instance().registerCommand("last", Last::create);
}
