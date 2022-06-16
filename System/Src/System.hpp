#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_

#include <vector>
#include <iostream>
#include <string>
#include <array>
#include <map>

class Flight;
class Cflight;
class Ticket;
class User;
class Filter;
class Airline;
class Destination;

class System {
public:
    System() = default;
    ~System();

    void new_flight(const std::string&, const std::string&, const std::string&, const int&, 
         const std::string&, const int&, const std::string&, const int&, const float&);

    void signup(const std::string&, const std::string&);
    void login(const std::string&, const std::string&);
    void logout();

    void addCredits(const float&);    

    int buyTicket(const int&, const int&, const std::string&, const std::string&);
    void deleteTicket(const int&);

    std::vector<Flight*> getFlights();
    std::string getC_Flights(const std::string&, const std::string&);
    std::string getFlight(const int&);
    std::string getCheapestFlight(const std::string&, const std::string&, const int&);

    void filter_airline(std::string);  
    void filter_cost(float, float);
    void filter_from(std::string, std::string);
    void filter_time(std::string, std::string, int);

    void addFilter(Filter*);
    void deleteFilters();

    std::string toStringFlights(const std::vector<Flight*>&) const;
    std::string toStringC_Flights(const std::vector<Cflight*>&) const;

    float average_flight_cost() const;
    float max_flight_cost() const;
    float min_flight_cost() const;

    int is_existed_airline(const std::string&) const;
    int is_existed_destination(const std::string&) const;

    void newTicketData(Ticket*);
    void recieveDatas();
    std::string overallReport();

    User* whatUser() const;
    User* loggedInUser_ = nullptr;
private:
    User* find_user(const std::string&);
    Flight* find_flight(const int&);
    std::vector<Cflight*> find_Cflights(const std::string&, const std::string&);

    Filter* filter_;

    std::vector<User*> users_;
    std::vector<Flight*> flights_;
    std::vector<Ticket*> tickets_;
    std::map<std::string, int> airlines_;
    std::map<std::string, int> destinations_;
};

#endif