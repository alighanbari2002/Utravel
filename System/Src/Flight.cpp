#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "Time.hpp"
#include "Flight.hpp"
#include "Utils.hpp"
#include "Functions.hpp"

Flight::Flight(const string& airline_, const string& origin_, const string& destination_, 
    const int& departure_date_, const string& departure_time_, const int& arrival_date_, 
    const string& arrival_time_, int seats_, const float& cost_) {

        airline = airline_; origin = origin_; destination = destination_; 
        departure_date = departure_date_; arrival_date = arrival_date_;
        departure_time.receive_Time(departure_time_); id = new_fight_id(); 
        business_seats = (seats_ / consts::BUSINESS_PERCENTAGE) + ((seats_ % consts::BUSINESS_PERCENTAGE) != 0);
        arrival_time.receive_Time(arrival_time_); cost = cost_; economy_seats = seats_ - business_seats;
}

bool Flight::is_same_flight(const int& id_) const { return id == id_; }

bool Flight::is_same_date(const int& date_) const { return departure_date == date_; }

bool Flight::has_enough_capacity(const int& quantity_, const std::string& class_type_) {
    if(class_type_ == enum_str[economy]) return quantity_ <= economy_seats;
    else return quantity_ <= business_seats;
}

bool Flight::can_be_connect(Flight* fCheck, const std::string& from_, const std::string& to_, Time& time, float& total_cost) {
    time.receive_Time("00:00"); total_cost = 0;
    if(this->origin != from_ || fCheck->destination != to_ || this->destination != fCheck->origin) return false;
    ostringstream os; os << fCheck->departure_time;
    if(this->arrival_date == fCheck->departure_date) {
        if(this->arrival_time.is_larger_than(os.str())) return false;
        time.time_interval(this->arrival_time, fCheck->departure_time);
    }
    else if(this->arrival_date == fCheck->departure_date - 1)
        time.time_interval(this->arrival_time, fCheck->departure_time, 1);
    else return false;
    if(time.is_larger_than("15:00")) return false;
    total_cost = this->cost + fCheck->cost;
    return true;
}

bool Flight::filter_path(const std::string& departure_, const std::string& destination_) const {
    return (origin == departure_ && destination == destination_);
}

bool Flight::filter_airline(const std::string& airline_) const {
    return airline == airline_;
}

bool Flight::filter_cost(const float& min, const float& max) const {
    if(min == consts::WRONG_COST) return cost <= max;
    else if(max == consts::WRONG_COST) return cost >= min;
    else return (cost >= min && cost <= max);
}

bool Flight::filter_time(string min, string max, const int& date) const {
    if(departure_date == date) {
        if(min == consts::WRONG_TIME_FORMAT) min = "00:00";
        if(max == consts::WRONG_TIME_FORMAT) max = "24:00";
        if(departure_time.is_equal(min) || departure_time.is_equal(max)) return true;
        else return (departure_time.is_larger_than(min) && !departure_time.is_larger_than(max));
    }
    else return false;
}

void Flight::reserve_seats(const int& quantity_, const string& class_type_) {
    (class_type_ == enum_str[economy]) ? economy_seats -= quantity_ : business_seats -= quantity_;
}

float Flight::get_cost() const { return cost; }

string Flight::get_deTime() const {
    ostringstream sstr;
    sstr << departure_time;
    return sstr.str();
}

string Flight::get_arTime() const {
    ostringstream sstr;
    sstr << arrival_time;
    return sstr.str();
}

string Flight::toStringFlight() const {
    ostringstream sstr;
    sstr << id << ' ' << airline << ' ' << origin << ' ' << destination << ' ' << departure_date << ' ' << departure_time << 
    ' ' << arrival_date << ' ' << arrival_time << ' ' << economy_seats + business_seats << ' ' << to_print_float(cost);
    return sstr.str();
}