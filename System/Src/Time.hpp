#ifndef _TIME_HPP_
#define _TIME_HPP_

#include <iostream>
#include <string>

class Time {
public:
    Time() = default;
    void receive_Time(std::string);

    bool is_larger_than(std::string) const;
    bool is_equal(std::string) const;

    void time_interval(Time, Time, const int& mode = 0);

    std::string toStringTime();
    friend std::ostream& operator<<(std::ostream& out, const Time& t);
private:
    int hour, minute;
};

#endif