#ifndef _BAD_REQ_HPP_
#define _BAD_REQ_HPP_

#include <exception>

class BadReq : public std::exception {
public:
    const char* what() const noexcept override {
        return "Bad Request";
    }
};

#endif