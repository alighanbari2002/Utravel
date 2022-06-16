#ifndef _NOT_FOUND_HPP_
#define _NOT_FOUND_HPP_

#include <exception>

class NotFound : public std::exception {
public:
    const char* what() const noexcept override {
        return "Not Found";
    }
};

#endif