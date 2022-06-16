#ifndef _TICKET_HPP_
#define _TICKET_HPP_

#include <string>
#include <vector>
#include <iostream>

class Flight;

class Ticket {
public:
    Ticket(Flight*, const std::string&, const std::string&, 
        const int&, const float&, const int&);
    ~Ticket();

    bool is_same_Ticket(const int&) const;
    bool is_refundable() const;

    float get_price() const;

    void cancelTicket() const;

    void datasToAdd(std::string&, std::string&) const;
    std::string toStringTicket();
private:
    int id, quantity;
    bool refundable;
    std::string class_type;
    Flight* flight_destination;
    float price;
};

#endif