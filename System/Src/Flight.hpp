#ifndef _FLIGHT_HPP_
#define _FLIGHT_HPP_

#include <string>
#include <vector>
#include <iostream>

#include "Time.hpp"

class System;

class Flight {
public:
    Flight(const std::string&, const std::string&, const std::string&, 
        const int&, const std::string&, const int&, const std::string&, int, const float&);

    bool is_same_flight(const int&) const;
    bool is_same_date(const int&) const;
    bool has_enough_capacity(const int&, const std::string&);
    bool can_be_connect(Flight*, const std::string&, const std::string&, Time&, float&);

    //filters function
    bool filter_path(const std::string&, const std::string&) const;
    bool filter_airline(const std::string&) const;
    bool filter_cost(const float&, const float&) const;
    bool filter_time(std::string, std::string, const int&) const;

    void reserve_seats(const int&, const std::string&);

    float get_cost() const;
    int get_deDate() const { return departure_date; }
    int get_arDate() const { return arrival_date; }
    int get_seats() const { return economy_seats + business_seats; }
    int get_id() const { return id; }
    std::string get_airline() const { return airline; }
    std::string get_origin() const { return origin; }
    std::string get_des() const { return destination; }
    std::string get_deTime() const;
    std::string get_arTime() const;

    std::string toStringFlight() const;
    
    friend class Ticket;
private:
    std::string airline, origin, destination;
    int departure_date, arrival_date, economy_seats, business_seats, id;
    Time departure_time, arrival_time;
    float cost;
};

#endif