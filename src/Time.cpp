//
// Created by User on 01.02.2026..
//

#include "Time.h"
#include "Exception.h"
#include <ctime>
#include <iostream>
Time::Time(std::istream& input, std::ostream& output)
    : Command(input, output){
}


void Time::execute()
{
    std::time_t currentTime = std::time(nullptr);

    std::tm localTime;
    localtime_s(&localTime, &currentTime);

    int hour = localTime.tm_hour;
    int min = localTime.tm_min;
    int sec = localTime.tm_sec;

    *output
        << (hour < 10 ? "0" : "") << hour << ":"
        << (min < 10 ? "0" : "") << min << ":"
        << (sec < 10 ? "0" : "") << sec
        << std::endl;

}


std::unique_ptr<Command> Time::create(const CommandContext& ctx) {
    if (!ctx.argument.empty()) {
        throw Exception("Funkcija ne treba da prima argument");
    }
    return std::make_unique<Time>(*ctx.input, *ctx.output);
}
