#ifndef _FILTER_FROM_
#define _FILTER_FROM_

#include <string>

#include "Filter.hpp"

class FilterFrom : public Filter {
public:
    FilterFrom(std::string departure, std::string destination);

    std::vector<Flight*> filter(const std::vector<Flight*>& flights) const override;
    Filter::Type getType() const override;

private:
    static Filter::Type filterType_;

    std::string departure_;
    std::string destination_;
};

#endif