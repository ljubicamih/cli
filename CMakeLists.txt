cmake_minimum_required(VERSION 4.0)
project(projekat)

set(CMAKE_CXX_STANDARD 20)

add_executable(projekat main.cpp
        src/Command.cpp
        h/Command.h
        # DODATO PRI REFAKTORISANJU - sledecih pet linija (CommandContext.h, CommandRegistry.cpp/.h, CommandRegistrations.cpp/.h):
        h/CommandContext.h
        src/CommandRegistry.cpp
        h/CommandRegistry.h
        src/CommandRegistrations.cpp
        h/CommandRegistrations.h
        src/Date.cpp
        h/Date.h
        src/Echo.cpp
        h/Echo.h
        # DODATO PRI REFAKTORISANJU - nova komanda "exit":
        src/Exit.cpp
        h/Exit.h
        # DODATO PRI REFAKTORISANJU - nova komanda "last":
        src/Last.cpp
        h/Last.h
        src/Interpreter.cpp
        h/Interpreter.h
        src/Parser.cpp
        h/Parser.h
        src/Time.cpp
        h/Time.h
        src/Touch.cpp
        h/Touch.h
        src/WordCount.cpp
        h/WordCount.h
        src/Prompt.cpp
        h/Prompt.h
        src/Remove.cpp
        h/Remove.h
        src/Translate.cpp
        h/Translate.h
        src/Head.cpp
        h/Head.h
        src/Batch.cpp
        h/Batch.h
        src/Exception.cpp
        h/Exception.h
        src/Truncate.cpp
        h/Truncate.h
)

target_include_directories(projekat PRIVATE h)
