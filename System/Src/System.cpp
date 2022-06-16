#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>
#include <map>
#include <set>
using namespace std;

#include "Functions.hpp"
#include "System.hpp"
#include "Ticket.hpp"
#include "Cflight.hpp"
#include "Flight.hpp"
#include "Utils.hpp"
#include "User.hpp"
//exceptions
#include "../Exception/Bad_req.hpp"
#include "../Exception/Not_found.hpp"
#include "../Exception/Permission_denied.hpp"
//filters
#include "../Filter/Filter.hpp"
#include "../Filter/Filter_airline.hpp"
#include "../Filter/Filter_cost.hpp"
#include "../Filter/Filter_time.hpp"
#include "../Filter/Filter_from.hpp"


System::~System() {
    for (User* u : users_) delete u;
    for (Flight* f : flights_) delete f;
    for (Ticket* t : tickets_) delete t;
    airlines_.clear();
    destinations_.clear();
    delete loggedInUser_;
    deleteFilters();
}

void System::new_flight(const string& airline_, const string& origin_, const string& destination_, const int& departure_date_, 
    const string& departure_time_, const int& arrival_date_, const string& arrival_time_, const int& seats_, const float& cost_) {

        Flight* flight = new Flight(airline_, origin_, destination_, departure_date_,
         departure_time_, arrival_date_, arrival_time_, seats_, cost_);

         flights_.push_back(flight);

}

void System::signup(const std::string& username, const std::string& password) {
    if (loggedInUser_ != nullptr) throw PermissionDenied();
    User* u = find_user(username);
    if (u != nullptr) throw BadReq();

    User* newUser = new User(username, password);

    users_.insert(upper_bound(users_.begin(), users_.end(), newUser, User::nameCompare), newUser);
    loggedInUser_ = newUser;
}

void System::login(const std::string& username, const std::string& password) {
    if (loggedInUser_ != nullptr) throw PermissionDenied();
    User* u = find_user(username);
    if (u == nullptr) throw BadReq();
    if (!u->isPassword(password)) throw BadReq();
    loggedInUser_ = u;
}

void System::logout() {
    if (loggedInUser_ == nullptr) throw PermissionDenied();
    this->deleteFilters();
    loggedInUser_ = nullptr;
}

void System::addCredits(const float& amount) {
    if (loggedInUser_ == nullptr) throw PermissionDenied();

    if (amount < 0) throw BadReq();
    loggedInUser_->chargCredit(amount);
}

int System::buyTicket(const int& flight_id, const int& quantity, const std::string& class_, const std::string& type) {
    if (loggedInUser_ == nullptr) throw PermissionDenied();
    float price = 0;
    Flight* f = find_flight(flight_id);
    if (f == nullptr) throw NotFound();

    if(!f->has_enough_capacity(quantity, class_)) throw BadReq();
    if(!loggedInUser_->has_enough_money(f->get_cost() * quantity, class_, price)) throw BadReq();//mul

    int new_id = new_ticket_id(); 
    f->reserve_seats(quantity, class_); loggedInUser_->chargCredit(-price);
    tickets_.push_back(new Ticket(f, class_, type, new_id, price, quantity));
    loggedInUser_->addTicket(tickets_.back()); 
    return new_id;
}

void System::deleteTicket(const int& id) {
    if (loggedInUser_ == nullptr) throw PermissionDenied();
    Ticket* t = loggedInUser_->find_ticket(id);
    
    loggedInUser_->deleteTicket(t);
    tickets_.erase(find(tickets_.begin(), tickets_.end(), t));
}

void System::filter_airline(string airline) {
    if (loggedInUser_ == nullptr) throw PermissionDenied();

   this->addFilter(new FilterAirline(airline));
}

void System::filter_cost(float min, float max) {
    if (loggedInUser_ == nullptr) throw PermissionDenied();

    this->addFilter(new FilterCost(min, max));
}

void System::filter_from(string from, string to) {
    if (loggedInUser_ == nullptr) throw PermissionDenied();

    this->addFilter(new FilterFrom(from, to));
}

void System::filter_time(string min, string max, int date) {
    if (loggedInUser_ == nullptr) throw PermissionDenied();

    this->addFilter(new FilterTime(min, max, date));
}

vector<Flight*> System::getFlights() {
    if (loggedInUser_ == nullptr) throw PermissionDenied();

    if (flights_.empty()) throw NotFound();

    if (loggedInUser_->is_filtered()) {
        vector<Flight*> filtered = filter_->filter(flights_);

        if (filtered.empty()) throw NotFound();
        return filtered;
    }
    return flights_;
}

string System::getFlight(const int& id) {
    if (loggedInUser_ == nullptr) throw PermissionDenied();

    if (flights_.empty()) return consts::EMPTY;

    Flight* f = find_flight(id);
    if (f == nullptr) throw NotFound();

    return f->toStringFlight();
}

string System::getC_Flights(const string& from, const string& to) {
    if (loggedInUser_ == nullptr) throw PermissionDenied();
    vector<Cflight*> cflights_ = find_Cflights(from, to);
    if(cflights_.empty()) throw NotFound();

    return toStringC_Flights(cflights_);
}

Cflight* findCheapest_Cflight(const std::vector<Cflight*>& cflights_, const int& departure_date_) {
    for(Cflight* cf: cflights_)
        if(cf->is_same_date(departure_date_))
            return cf;
    return nullptr;
}

bool comparePtrToFlight(Flight* a, Flight* b) { return (a->get_cost() < b->get_cost()); }

Flight* findCheapest_Flight(std::vector<Flight*>& Flights_, const int& departure_date_) {
    sort(Flights_.begin(), Flights_.end(), comparePtrToFlight);
    for(Flight* f: Flights_)
        if(f->is_same_date(departure_date_))
            return f;
    return nullptr;
}

string toStringCheapest(Cflight* cf, Flight* f) {
    ostringstream os;
    if (cf!= nullptr && (f == nullptr || cf->is_cheaper_than(f->get_cost()))) return cf->toStringC_flight(1);
    else {
        os << f->toStringFlight() << '\n' << "Total cost: " << to_print_float(f->get_cost());
        return os.str();  
    }
}

string System::getCheapestFlight(const string& from, const string& to, const int& departure_date) {
    if (loggedInUser_ == nullptr) throw PermissionDenied();
    Cflight* cf; Flight* f;
    cf = findCheapest_Cflight(find_Cflights(from, to), departure_date);
    Filter* filter = new FilterFrom(from, to);
    vector<Flight*> flights =  filter->filter(flights_); delete filter;
    f = findCheapest_Flight(flights, departure_date);
    if(f == nullptr && cf == nullptr) throw NotFound();
    
    return toStringCheapest(cf, f);
}

void System::addFilter(Filter* filter) {
    deleteFilters();
    filter_ = filter;
    loggedInUser_->set_filter_status(true);
}

void System::deleteFilters() {
    if (loggedInUser_ == nullptr) throw PermissionDenied();
    
    filter_ = nullptr;
    loggedInUser_->set_filter_status(false);
}

string System::toStringFlights(const vector<Flight*>& flights) const {
    ostringstream sstr;
    for (unsigned i = 0; i < flights.size() - 1; i++) {
        sstr << flights[i]->toStringFlight() << '\n';
    }
    sstr << flights.back()->toStringFlight();
    return sstr.str();
}

string System::toStringC_Flights(const vector<Cflight*>& cFlights) const {
    ostringstream sstr;
    for (unsigned i = 0; i < cFlights.size() - 1; i++) {
        sstr << cFlights[i]->toStringC_flight() << '\n';
    }
    sstr << cFlights.back()->toStringC_flight();
    return sstr.str();
}

float System::average_flight_cost() const {
    float average = 0;
    for(Flight* f: flights_)
        average += f->get_cost();
    return average / flights_.size();
}

float System::max_flight_cost() const {
    float max = flights_.front()->get_cost();
    for(Flight* f: flights_)
        if(max < f->get_cost())
            max = f->get_cost();
    return max;
}

float System::min_flight_cost() const {
    float min = flights_.front()->get_cost();
    for(Flight* f: flights_)
        if(min > f->get_cost())
            min = f->get_cost();
    return min;
}

User* System::whatUser() const { return loggedInUser_; }

void System::newTicketData(Ticket* ticket) {
    string airline, destination;
    ticket->datasToAdd(destination, airline);

    auto result1 = airlines_.insert(std::pair<std::string, int>(airline, 1));
    if (result1.second == false)
        result1.first->second++;

    auto result2 = destinations_.insert(std::pair<std::string, int>(destination, 1));
    if (result2.second == false)
        result2.first->second++;
}

struct comp {
    template<typename T>
    bool operator()(const T &l, const T &r) const {
        if (l.second != r.second)
            return l.second < r.second;
        return l.first < r.first;
    }
};

void System::recieveDatas() {
    for (Ticket* t : tickets_) this->newTicketData(t);
    std::set<std::pair<std::string, int>, comp> set1(airlines_.begin(), airlines_.end());
    std::set<std::pair<std::string, int>, comp> set2(destinations_.begin(), destinations_.end());
}

std::string System::overallReport() {
    recieveDatas(); ostringstream os_; int i = 0;
    os_ << "average_flight_cost: " << to_print_float(average_flight_cost()) << '\n' <<
    "min_flight_cost: " << to_print_float(min_flight_cost()) << '\n' <<
    "max_flight_cost: " << to_print_float(max_flight_cost()) << '\n' <<
    "most_popular_destination: "; 
    if(destinations_.size() != 0) os_ << destinations_.begin()->first;
    else os_ << "Not Found";
    os_ << '\n' << "top_airlines: ";
    if(airlines_.size() != 0) 
        for(auto it = airlines_.begin(); i < 3; ++it, ++i) {
            if(airlines_.size() >= i + 1) {
                os_ << it->first;
                if(i != 2) os_ << ' ';
            } else break;
        }
    else os_ << "Not Found";
    return os_.str();
}

bool comparePtrToCflight(Cflight* a, Cflight* b) { return (a->totalCost < b->totalCost); }

vector<Cflight*> System::find_Cflights(const string& from, const string& to) {
    vector<Cflight*> Cflights_; Time t; float totalCost;
    for (Flight* f1 : flights_)
        for (Flight* f2 : flights_) 
            if(f1->can_be_connect(f2, from, to, t, totalCost))
                Cflights_.push_back(new Cflight(f1, f2, t, totalCost));

    sort(Cflights_.begin(), Cflights_.end(), comparePtrToCflight);
    return Cflights_;
}

Flight* System::find_flight(const int& id_) {
    for (Flight* f : flights_) {
        if (f->is_same_flight(id_)) return f;
    }
    return nullptr;
}

User* System::find_user(const string& username) {
    for (User* u : users_) {
        if (u->get_username() == username) return u;
    }
    return nullptr;
}