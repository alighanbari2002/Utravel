#ifndef _FUNCTIONS_HPP_
#define _FUNCTIONS_HPP_

#include <string>
#include <iostream>

enum Type {
    economy,
    business
};

static const char *enum_str[] =
        {"economy", "business"};

std::string argument_file(int argc, char* argv[]);

int new_fight_id();
int new_ticket_id();

std::string to_print_float(float);

#endif