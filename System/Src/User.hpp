#ifndef _USER_HPP_
#define _USER_HPP_

#include <string>
#include <vector>
#include <iostream>

class Ticket;

class User {
public:
    User(const std::string&, const std::string&);
    ~User();
    
    bool isPassword(const std::string&) const;
    bool has_enough_money(const float&, const std::string&, float&);
    bool is_filtered() const;

    std::string get_username() const;

    void addTicket(Ticket* ticket);
    void deleteTicket(Ticket*);

    void chargCredit(const float&);
    void set_filter_status(bool);

    std::string getTickets();
    std::string getTicket(const int&);

    static bool nameCompare(const User*, const User*);
    std::string getUsername() { return username_; }

    Ticket* find_ticket(const int&);

    std::string toStringTickets() const;
private:
    float credit_ = 0;
    bool isFilter;

    std::vector<Ticket*> tickets;
    std::string username_;
    std::string password_;
};

#endif 