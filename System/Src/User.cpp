#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

#include "User.hpp"
#include "Utils.hpp"
#include "Functions.hpp"
#include "Ticket.hpp"
#include "../Exception/Bad_req.hpp"
#include "../Exception/Not_found.hpp"

User::User(const std::string& username, const std::string& password)
    : username_(username),
      password_(password) {
}

User::~User() {
    for (Ticket* t : tickets) delete t;
}

string User::get_username() const { return username_; }

bool User::nameCompare(const User* u1, const User* u2) {
    return u1->get_username() < u2->get_username();
}

bool User::isPassword(const std::string& password) const { return password_ == password; }

bool User::has_enough_money(const float& flight_cost_, const std::string& ticket_type_, float& ticket_price_) {
    ticket_price_ = flight_cost_;
    if(ticket_type_ == enum_str[business]) ticket_price_ *= 2.5;
    return credit_ >= ticket_price_;
}

bool User::is_filtered() const { return isFilter; }

void User::addTicket(Ticket* ticket) {
    tickets.push_back(ticket);
}

void User::deleteTicket(Ticket* t) {
    if (t == nullptr) throw NotFound();
    if(!t->is_refundable()) throw BadReq();

    t->cancelTicket();
    this->chargCredit(t->get_price() * 0.5);
    tickets.erase(find(tickets.begin(), tickets.end(), t));
}

void User::chargCredit(const float& amount) { credit_ += amount; }

void User::set_filter_status(bool status) {
    isFilter = status;
}

string User::getTickets() {
    if (tickets.empty()) return consts::EMPTY;

    return toStringTickets();
}

string User::getTicket(const int& id) {
    if (tickets.empty()) return consts::EMPTY;

    Ticket* t = find_ticket(id);
    if (t == nullptr) throw NotFound();

    return t->toStringTicket();
}

string User::toStringTickets() const {
    std::ostringstream sstr;
    for (unsigned i = 0; i < tickets.size() - 1; i++) {
        sstr << tickets[i]->toStringTicket() << '\n';
    }
    sstr << tickets.back()->toStringTicket();
    return sstr.str();
}

Ticket* User::find_ticket(const int& id_) {
    for (Ticket* t : tickets) {
        if (t->is_same_Ticket(id_)) return t;
    }
    return nullptr;
}