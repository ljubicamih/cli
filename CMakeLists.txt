cmake_minimum_required(VERSION 4.0)
project(projekat)

set(CMAKE_CXX_STANDARD 20)

add_executable(projekat main.cpp
        Command.cpp
        Command.h
        # DODATO PRI REFAKTORISANJU - sledecih pet linija (CommandContext.h, CommandRegistry.cpp/.h, CommandRegistrations.cpp/.h):
        CommandContext.h
        CommandRegistry.cpp
        CommandRegistry.h
        CommandRegistrations.cpp
        CommandRegistrations.h
        Date.cpp
        Date.h
        Echo.cpp
        Echo.h
        # DODATO PRI REFAKTORISANJU - nova komanda "exit":
        Exit.cpp
        Exit.h
        # DODATO PRI REFAKTORISANJU - nova komanda "last":
        Last.cpp
        Last.h
        Interpreter.cpp
        Interpreter.h
        Parser.cpp
        Parser.h
        Time.cpp
        Time.h
        Touch.cpp
        Touch.h
        WordCount.cpp
        WordCount.h
        Prompt.cpp
        Prompt.h
        Remove.cpp
        Remove.h
        Translate.cpp
        Translate.h
        Head.cpp
        Head.h
        Batch.cpp
        Batch.h
        Exception.cpp
        Exception.h
        Truncate.cpp
        Truncate.h
)