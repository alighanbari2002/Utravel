#include "Filter_from.hpp"

#include "../Src/Flight.hpp"

Filter::Type FilterFrom::filterType_ = Filter::Type::from;

FilterFrom::FilterFrom(std::string departure, std::string destination)
    : departure_(departure),
      destination_(destination) {}

std::vector<Flight*> FilterFrom::filter(const std::vector<Flight*>& flights) const {
    std::vector<Flight*> filtered;
    for (Flight* f : flights) {
        if (f->filter_path(departure_, destination_)) {
            filtered.push_back(f);
        }
    }
    return filtered;
}

Filter::Type FilterFrom::getType() const { return filterType_; }