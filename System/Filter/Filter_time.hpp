#ifndef _FILTER_TIME_
#define _FILTER_TIME_

#include <string>

#include "Filter.hpp"

class FilterTime : public Filter {
public:
    FilterTime(std::string time_min, std::string time_max, int departure_date);

    std::vector<Flight*> filter(const std::vector<Flight*>& flights) const override;
    Filter::Type getType() const override;

private:
    static Filter::Type filterType_;

    std::string min_;
    std::string max_;
    int date_;
};

#endif