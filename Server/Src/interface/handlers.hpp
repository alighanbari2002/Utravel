#ifndef _HANDLERS_HPP_
#define _HANDLERS_HPP_

#include "../server/server.hpp"

constexpr int SID_LENGTH = 10;

class SystemInterface;

class CasHandler : public RequestHandler {
public:
    CasHandler(SystemInterface& si, const std::string& casPage);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
    ShowPage* casPage_;
};

class LoginHandler : public RequestHandler {
public:
    LoginHandler(SystemInterface& si);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
};

class SignupHandler : public RequestHandler {
public:
    SignupHandler(SystemInterface& si);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
};

class LogoutHandler : public RequestHandler {
public:
    LogoutHandler(SystemInterface& si);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
};

class HomepageHandler : public RequestHandler {
public:
    HomepageHandler(SystemInterface& si, const std::string& homePage);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
    ShowPage* homePage_;
};

class HomepageJsHandler : public RequestHandler {
public:
    HomepageJsHandler(SystemInterface& si);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
};

class NavbarHandler : public RequestHandler {
public:
    NavbarHandler(SystemInterface& si);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
};


class AddFlightHandler : public RequestHandler {
public:
    AddFlightHandler(SystemInterface& si);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
};

class DelFlightHandler : public RequestHandler {
public:
    DelFlightHandler(SystemInterface& si);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
};

class Recipe;
class FlightMoreInfoTemplateHandler : public TemplateHandler {
public:
    FlightMoreInfoTemplateHandler(const std::string& filePath, SystemInterface& si);
    std::map<std::string, std::string> handle(Request* req) override;
    void setRecipe(Recipe* recipe);

private:
    Recipe* recipe_ = nullptr;
    SystemInterface& si_;
};
class FlightMoreInfoHandler : public RequestHandler {
public:
    FlightMoreInfoHandler(SystemInterface& si, const std::string& filePath);
    Response* callback(Request* req) override;

private:
    FlightMoreInfoTemplateHandler t_;
    SystemInterface& si_;
};

class FilterHandler : public RequestHandler {
public:
    FilterHandler(SystemInterface& si);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
};

class GetFiltersHandler : public RequestHandler {
public:
    GetFiltersHandler(SystemInterface& si);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
};

class DelFiltersHandler : public RequestHandler {
public:
    DelFiltersHandler(SystemInterface& si);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
};

class RateHandler : public RequestHandler {
public:
    RateHandler(SystemInterface& si);
    Response* callback(Request* req) override;

private:
    SystemInterface& si_;
};

class ShowFileJs : public RequestHandler {
public:
    ShowFileJs(const std::string& path);
    Response* callback(Request* req) override;

private:
    std::string path_;
};

#endif // HANDLERS_HPP_INCLUDE