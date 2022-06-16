#include <string>
#include <sstream>
using namespace std;

#include "Time.hpp"

void Time::receive_Time(string timeStr) {
    string str; stringstream ss(timeStr);
    getline(ss, str, ':');
    hour = stoi(str);
    getline(ss, str);
    minute = stoi(str);
}

bool Time::is_larger_than(string timeStr) const {
    Time time; time.receive_Time(timeStr);
    return (this->hour > time.hour) || (this->hour == time.hour && this->minute > time.minute);
}

bool Time::is_equal(string timeStr) const {
    Time time; time.receive_Time(timeStr);
    return(this->hour == time.hour && this->minute == time.minute);
}

void Time::time_interval(Time begin, Time end, const int& mode) {
    hour = end.hour - begin.hour;
    minute = end.minute - begin.minute;
    
    if(mode != 0)
        hour += 24;
    
    while(minute < 0) {
        minute += 60;
        hour -= 1;
    }
}

string Time::toStringTime() {
    ostringstream os;
    os << hour <<"h " << minute << "m";
    return os.str();
}

ostream& operator<<(ostream& out, const Time& t) {
    if (t.hour / 10 == 0) out << "0";
    out << t.hour << ":";
    if (t.minute / 10 == 0) out << "0";
    out << t.minute;
    return out;
}