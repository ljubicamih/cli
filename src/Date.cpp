//
// Created by User on 31.01.2026..
//

#include "Date.h"
#include "Exception.h"  // DODATO PRI REFAKTORISANJU
#include <iostream>
#include <ctime>

Date::Date(std::istream& input, std::ostream& output) : Command(input, output){}

void Date::execute()
{
    std::time_t currentTime = std::time(nullptr);   // trenutno vreme u sekundama
    std::tm* date = std::localtime(&currentTime);

    int day = date->tm_mday;
    int month = date->tm_mon + 1;
    int year = date->tm_year + 1900;

    *output
        << (day < 10 ? "0" : "") << day << "."
        << (month < 10 ? "0" : "") << month << "."
        << year
        << std::endl;
}



std::unique_ptr<Command> Date::create(const CommandContext& ctx) {
    if (!ctx.argument.empty()) {
        throw Exception("Funkcija ne treba da prima argument");
    }
    return std::make_unique<Date>(*ctx.input, *ctx.output);
}
