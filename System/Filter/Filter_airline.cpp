#include "Filter_airline.hpp"

#include "../Src/Flight.hpp"

Filter::Type FilterAirline::filterType_ = Filter::Type::airline;

FilterAirline::FilterAirline(std::string airline)
    : airline_(airline) {}

std::vector<Flight*> FilterAirline::filter(const std::vector<Flight*>& flights) const {
    std::vector<Flight*> filtered;
    for (Flight* f : flights) {
        if (f->filter_airline(airline_)) {
            filtered.push_back(f);
        }
    }
    return filtered;
}

Filter::Type FilterAirline::getType() const { return filterType_; }