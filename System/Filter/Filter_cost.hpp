#ifndef _FILTER_COST_
#define _FILTER_COST_

#include "Filter.hpp"

class FilterCost : public Filter {
public:
    FilterCost(float min_price, float max_price);

    std::vector<Flight*> filter(const std::vector<Flight*>& flights) const override;
    Filter::Type getType() const override;

private:
    static Filter::Type filterType_;

    float min_price_;
    float max_price_;
};

#endif