#ifndef _FILTER_HPP_
#define _FILTER_HPP_

#include <vector>

class Flight;

class Filter {
public:
    virtual ~Filter() {};

    virtual std::vector<Flight*> filter(const std::vector<Flight*>& flights) const = 0;

    enum class Type {
        from,
        airline,
        cost_period,
        time_period
    };
    
    virtual Filter::Type getType() const = 0;
};

#endif 