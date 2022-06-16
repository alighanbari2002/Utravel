#ifndef _SYSTEM_INTERFACE_HPP_
#define _SYSTEM_INTERFACE_HPP_

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "../../../System/Src/Utils.hpp"
#include "../../../System/Exception/Bad_req.hpp"
#include "../../../System/Exception/Not_found.hpp"
#include "../../../System/Exception/Permission_denied.hpp"
#include "../../../System/Filter/Filter.hpp"
#include "../../../System/Src/Ticket.hpp"
#include "../../../System/Src/Flight.hpp"
#include "../../../System/Src/System.hpp"
#include "../../../System/Src/User.hpp"

constexpr std::chrono::minutes TIMEOUT_MIN(20);

class User;

class SystemInterface {
public:
    SystemInterface();
    ~SystemInterface();

    void recieve_flights(int argc, char* argv[]);

    System& operator()(const std::string& sid);

    bool isLoggedIn(const std::string& sid);
    User* getUser(const std::string& sid);
    bool sidExists(const std::string& sid) const;
    void addSid(const std::string& sid);
    void removeSid(const std::string& sid);
private:
    System sys_;

    void checkForTimeout();
    std::thread th_;
    std::mutex mtex_;
    std::atomic<bool> endTimeoutThread_ = {false};
    std::condition_variable cv_;

    using Clock = std::chrono::steady_clock;
    using Time = std::chrono::time_point<Clock>;

    struct Account {
        User* u;
        Time lastAccess;
    };

    std::unordered_map<std::string, Account> loggedIns_;
};

#endif // SYSTEM_INTERFACE_HPP_INCLUDE