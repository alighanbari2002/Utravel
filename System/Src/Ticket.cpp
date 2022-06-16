#include <string>
#include <sstream>
using namespace std;

#include "Ticket.hpp"
#include "Flight.hpp"
#include "Functions.hpp"

Ticket::Ticket(Flight* flight_, const string& classType_, const string& ticket_type_, 
        const int& id_, const float& price_, const int& quantity_) {

            flight_destination = flight_; class_type = classType_;
            price = price_; id = id_; quantity = quantity_;
            (ticket_type_ == "refundable") ? refundable = true : refundable = false;
}

Ticket::~Ticket() { delete flight_destination; }

bool Ticket::is_same_Ticket(const int& id_) const { return id == id_; }

bool Ticket::is_refundable() const { return refundable; }

float Ticket::get_price() const { return price; }

void Ticket::cancelTicket() const {
    flight_destination->reserve_seats(-quantity, class_type);
}

void Ticket::datasToAdd(std::string& des_, std::string& air_) const {
    des_ = flight_destination->destination;
    air_ = flight_destination->airline; 
}

std::string Ticket::toStringTicket() {
    ostringstream sstr;
    sstr << id << ' ' << flight_destination->id << ' ' << flight_destination->airline << ' ' << quantity << ' ' <<
    flight_destination->origin << ' ' << flight_destination->destination << ' ' << flight_destination->departure_date << ' ' <<
    flight_destination->departure_time << ' ' << flight_destination->arrival_date << ' ' << flight_destination->arrival_time <<
    ' ' << class_type; (refundable) ? sstr << " refundable " : sstr << " nonrefundable ";
    sstr << to_print_float(price);
    return sstr.str();
}