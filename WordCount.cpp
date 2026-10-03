//
// Created by User on 01.02.2026..
//

#include "WordCount.h"
#include "Exception.h"

#include <iostream>

WordCount::WordCount(std::istream& input, std::ostream& output, const std::string& opt)
    : Command(input, output), option(opt) {
}


void WordCount::execute()
{
    // brojanje karaktera
    if (option == "-c") {
        int count = 0;
        char ch;

        while (input->get(ch)) {
            count++;
        }

        *output << count << std::endl;
    }

    // brojanje reci
    else if (option == "-w") {
        int count = 0;
        bool inWord = false;
        char ch;

        while (input->get(ch)) {
            if (isspace(ch)) {
                if (inWord) {   // ako smo prethodno bili u reci i naisli na space, zavrsili smo jednu rec
                    count++;
                    inWord = false;
                }
            }

            else {
                inWord = true;  // ako karakter nije razmak u reci smo
            }
        }

        // poslednja rec
        if (inWord)
            count++;

        *output << count << std::endl;
    }

    else {
        throw Exception("Nepostojeca opcija");
    }

    input->clear();
}


std::unique_ptr<Command> WordCount::create(const CommandContext& ctx) {
    return std::make_unique<WordCount>(*ctx.input, *ctx.output, ctx.option);
}
