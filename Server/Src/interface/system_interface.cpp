#include "system_interface.hpp"
#include "../../../System/Src/Functions.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>

SystemInterface::SystemInterface() {
    th_ = std::thread(&SystemInterface::checkForTimeout, this);
}

SystemInterface::~SystemInterface() {
    endTimeoutThread_ = true;
    cv_.notify_one();
    th_.join();
}

void SystemInterface::recieve_flights(int argc, char* argv[]) {
    std::ifstream fsIn(argument_file(argc, argv));
    std::string str, airline, origin, destination, departure_time, arrival_time;
    int departure_date, arrival_date, seats; float cost;
    std::getline(fsIn, str);
    while(std::getline(fsIn, str)) {
        std::stringstream ss(str);
        for(int i = 0; i < 9; i++) {
        std::getline(ss, str, ',');
        if(i == 0) airline = str;
        else if(i == 1) origin = str;
        else if(i == 2) destination = str;
        else if(i == 3) departure_date = stoi(str);
        else if(i == 4) departure_time = str;
        else if(i == 5) arrival_date = stoi(str);
        else if(i == 6) arrival_time = str;
        else if(i == 7) seats = stoi(str);
        else cost = stof(str);
        }
        sys_.new_flight(airline, origin, destination, departure_date, 
        departure_time, arrival_date, arrival_time, seats, cost);
    } fsIn.close();
}

void SystemInterface::checkForTimeout() {
    std::chrono::seconds delay(10);
    while (true) {
        std::unique_lock<std::mutex> gaurd(mtex_);
        if (cv_.wait_for(gaurd, delay, [this]() { return this->endTimeoutThread_.load(); })) return;

        for (auto itr = loggedIns_.begin(); itr != loggedIns_.end();) {
            if (std::chrono::duration_cast<std::chrono::minutes>(Clock::now() - itr->second.lastAccess) > TIMEOUT_MIN) {
                itr = loggedIns_.erase(itr);
            }
            else ++itr;
        }
    }
}

bool SystemInterface::sidExists(const std::string& sid) const {
    if (loggedIns_.find(sid) == loggedIns_.end()) return false;
    return true;
}

void SystemInterface::addSid(const std::string& sid) {
    loggedIns_[sid].u = sys_.loggedInUser_;
    loggedIns_[sid].lastAccess = Clock::now();
}

void SystemInterface::removeSid(const std::string& sid) {
    auto itr = loggedIns_.find(sid);
    if (itr == loggedIns_.end()) return;
    loggedIns_.erase(itr);
}

System& SystemInterface::operator()(const std::string& sid) {
    auto itr = loggedIns_.find(sid);
    if (itr == loggedIns_.end()) sys_.loggedInUser_ = nullptr;
    else {
        itr->second.lastAccess = Clock::now();
        sys_.loggedInUser_ = itr->second.u;
    }
    return sys_;
}

bool SystemInterface::isLoggedIn(const std::string& sid) {
    if (sid.empty()) return false;
    auto itr = loggedIns_.find(sid);
    if (itr == loggedIns_.end()) return false;
    itr->second.lastAccess = Clock::now();
    return true;
}

User* SystemInterface::getUser(const std::string& sid) {
    auto itr = loggedIns_.find(sid);
    if (itr == loggedIns_.end()) return nullptr;
    itr->second.lastAccess = Clock::now();
    return itr->second.u;
}