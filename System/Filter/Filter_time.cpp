#include "Filter_time.hpp"

#include "../Src/Flight.hpp"

Filter::Type FilterTime::filterType_ = Filter::Type::time_period;

FilterTime::FilterTime(std::string time_min, std::string time_max, int departure_date)
    : min_(time_min),
      max_(time_max),
      date_(departure_date) {}

std::vector<Flight*> FilterTime::filter(const std::vector<Flight*>& flights) const {
    std::vector<Flight*> filtered;
    for (Flight* f : flights) {
        if (f->filter_time(min_, max_, date_)) {
            filtered.push_back(f);
        }
    }
    return filtered;
}

Filter::Type FilterTime::getType() const { return filterType_; }