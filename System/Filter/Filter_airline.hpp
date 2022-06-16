#ifndef _FILTER_AIRLINE_
#define _FILTER_AIRLINE_

#include <string>

#include "Filter.hpp"

class FilterAirline : public Filter {
public:
    FilterAirline(std::string airline);

    std::vector<Flight*> filter(const std::vector<Flight*>& flights) const override;
    Filter::Type getType() const override;

private:
    static Filter::Type filterType_;
    
    std::string airline_;
};

#endif