#ifndef _CFLIGHT_HPP_
#define _CFLIGHT_HPP_

#include <vector>

#include "Time.hpp"

class Flight;

class Cflight {
public:
    Cflight(Flight*, Flight*, Time, float);

    bool is_same_date(const int&);
    bool is_cheaper_than(const int&);
    
    std::string toStringC_flight(const int& chap_mode = 0);

    friend bool comparePtrToCflight(Cflight* a, Cflight* b);
private:
    Flight* firstFlight;
    Flight* secondFlight;
    Time duration;
    float totalCost;
};

#endif