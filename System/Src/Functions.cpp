#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
using namespace std;

#include "Functions.hpp"    
#include "Utils.hpp"

string argument_file(int argc, char* argv[]) {
    string input = "";
    for(int i = 0; i < argc; i++) {
        input = argv[i];
        if(input.find(consts::CSV_FORMAT) == -1) continue;
        else return argv[i];
    }
    return "No such file found!";
}

int new_fight_id() {
    static int id = 0;
    id++;
    return id;
}

int new_ticket_id() {
    static int id_ = 0;
    id_++;
    return id_;
}

string to_print_float(float fVal) {
  fVal = floor(100 * fVal) / 100;
  ostringstream os_;
  os_ << fixed << setprecision(2) << fVal;
  return os_.str();
}