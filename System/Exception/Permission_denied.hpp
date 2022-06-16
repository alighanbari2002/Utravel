#ifndef _PERMISSION_DENIED_HPP_
#define _PERMISSION_DENIED_HPP_

#include <exception>

class PermissionDenied : public std::exception {
public:
    const char* what() const noexcept override {
        return "Permission Denied";
    }
};

#endif