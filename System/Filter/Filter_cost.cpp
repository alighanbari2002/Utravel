#include "Filter_cost.hpp"

#include "../Src/Flight.hpp"

Filter::Type FilterCost::filterType_ = Filter::Type::cost_period;

FilterCost::FilterCost(float min_price, float max_price)
    : min_price_(min_price),
      max_price_(max_price) {}

std::vector<Flight*> FilterCost::filter(const std::vector<Flight*>& flights) const {
    std::vector<Flight*> filtered;
    for (Flight* f : flights) {
        if (f->filter_cost(min_price_, max_price_)) {
            filtered.push_back(f);
        }
    }
    return filtered;
}

Filter::Type FilterCost::getType() const { return filterType_; }