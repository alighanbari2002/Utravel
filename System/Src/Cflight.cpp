#include <sstream>
using namespace std;

#include "Cflight.hpp"
#include "Flight.hpp"
#include "Functions.hpp"
#include "Time.hpp"

Cflight::Cflight(Flight* f1_, Flight* f2_, Time duration_, float totalCost_) {
    firstFlight = f1_; secondFlight = f2_;
    duration = duration_;
    totalCost = totalCost_;
}

bool Cflight::is_same_date(const int& departure_date_) {
    return (firstFlight->is_same_date(departure_date_));
}

bool Cflight::is_cheaper_than(const int& costCheck) {
    return totalCost < costCheck;
}

string Cflight::toStringC_flight(const int& chap_mode) {
    ostringstream sstr;
    sstr << "Flight 1: " << firstFlight->toStringFlight() << '\n' <<
    "Flight 2: " << secondFlight->toStringFlight() << '\n';
    if(chap_mode == 0) { 
    sstr << "* Connection duration: " << duration.toStringTime() << 
    ", Total cost: " << to_print_float(totalCost) << '\n' << "----------";
    }
    else sstr << "Total cost: " << to_print_float(totalCost);
    return sstr.str();
}