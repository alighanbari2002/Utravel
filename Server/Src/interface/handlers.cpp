#include "handlers.hpp"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include "system_interface.hpp"
#include "tools.hpp"

CasHandler::CasHandler(SystemInterface& si, const std::string& casPage) : si_(si) {
    casPage_ = new ShowPage(casPage);
}
Response* CasHandler::callback(Request* req) {
    if (si_.isLoggedIn(req->getSessionId())) {
        return Response::redirect("/home");
    }
    return casPage_->callback(req);
}

LoginHandler::LoginHandler(SystemInterface& si) : si_(si) {}
Response* LoginHandler::callback(Request* req) {
    std::string username = req->getBodyParam("username");
    std::string password = req->getBodyParam("password");
    if (username.empty() || password.empty()) {
        return Response::redirect("/400");
    }

    try {
        si_(req->getSessionId()).login(username, password);
    }
    catch (const BadReq& ex) {
        return Response::redirect("/400");
    }
    catch (const PermissionDenied& ex) {
        return Response::redirect("/401");
    }
    catch (const NotFound& ex) {
        return Response::redirect("/404");
    }

    Response* res = Response::redirect("/home");

    std::string SID;
    while (true) {
        SID = randString(SID_LENGTH);
        if (!si_.sidExists(SID)) break;
    }
    si_.addSid(SID);
    res->setSessionId(SID);

    return res;
}

SignupHandler::SignupHandler(SystemInterface& si) : si_(si) {}
Response* SignupHandler::callback(Request* req) {
    std::string username = req->getBodyParam("username");
    std::string password = req->getBodyParam("password");
    if (username.empty() || password.empty()) {
        return Response::redirect("/400");
    }

    try {
        si_(req->getSessionId()).signup(username, password);
    }
    catch (const BadReq& ex) {
        return Response::redirect("/400");
    }
    catch (const PermissionDenied& ex) {
        return Response::redirect("/401");
    }
    catch (const NotFound& ex) {
        return Response::redirect("/404");
    }

    Response* res = Response::redirect("/home");

    std::string SID;
    while (true) {
        SID = randString(SID_LENGTH);
        if (!si_.sidExists(SID)) break;
    }
    si_.addSid(SID);
    res->setSessionId(SID);

    return res;
}

LogoutHandler::LogoutHandler(SystemInterface& si) : si_(si) {}
Response* LogoutHandler::callback(Request* req) {
    try {
        si_(req->getSessionId()).logout();
    }
    catch (const BadReq& ex) {
        return Response::redirect("/400");
    }
    catch (const PermissionDenied& ex) {
        return Response::redirect("/401");
    }
    catch (const NotFound& ex) {
        return Response::redirect("/404");
    }

    Response* res = Response::redirect("/");

    si_.removeSid(req->getSessionId());
    res->setSessionId("");

    return res;
}

HomepageHandler::HomepageHandler(SystemInterface& si, const std::string& homePage)
    : si_(si) {
    homePage_ = new ShowPage(homePage);
}
Response* HomepageHandler::callback(Request* req) {
    if (!si_.isLoggedIn(req->getSessionId())) {
        return Response::redirect("/");
    }

    return homePage_->callback(req);
}

HomepageJsHandler::HomepageJsHandler(SystemInterface& si) : si_(si) {}
Response* HomepageJsHandler::callback(Request* req) {
    if (!si_.isLoggedIn(req->getSessionId())) {
        return Response::redirect("/");
    }

    std::vector<Flight*> f;
    User* u = si_.getUser(req->getSessionId());
    try {
            f = si_(req->getSessionId()).getFlights();
    }
    catch (const BadReq& ex) {
        return Response::redirect("/400");
    }
    catch (const PermissionDenied& ex) {
        return Response::redirect("/403");
    }
    catch (const NotFound& ex) {
        return Response::redirect("/404");
    }

    std::ostringstream sstr;
    sstr << "const flights = [\n";
    for (unsigned i = 0; i < f.size(); i++) {
        sstr << "new Flight(" << '"' << f[i]->get_id() << "\","
             << '"' << f[i]->get_airline() << "\","
             << '"' << f[i]->get_origin() << ','
             << '"' << f[i]->get_des() << ','
             << '"' << f[i]->get_cost() << ','
             << "\"),\n";
    }
    sstr << "];\n\n";

    sstr << "//loop to add flights to the page\n"
            "for (let i = 0; i < flights.length; i++) {\n"
            "  try {\n"
            "    addFlight(recipes[i], \"r\" + i, "
         << "\"More Info\""
         << ");\n"
            "  }\n"
            "  catch (err) {\n"
            "      console.log(err);\n"
            "  }\n"
            "};\n\n";
    Response* res = new Response();
    res->setHeader("Content-Type", "text/javascript");
    res->setBody(sstr.str());
    return res;
}

NavbarHandler::NavbarHandler(SystemInterface& si) : si_(si) {}
Response* NavbarHandler::callback(Request* req) {
    User* u = si_.getUser(req->getSessionId());
    if (u == nullptr) {
        return Response::redirect("/403.html");
    }

    std::string file = readFile("static/navbar/add_navbar.js");

    std::ostringstream sstr;
    sstr << "\n\nfunction ajaxAndLoad(url, onloadFunc) {\n"
            "  const xhttp = new XMLHttpRequest();\n"
            "    xhttp.onload = function () {\n"
            "      if (this.status == 200) {\n"
            "        onloadFunc(this.responseText);\n";

    sstr << "        document.getElementById(\"username\").innerHTML= \"";
    sstr << "User: ";

    sstr << u->getUsername() << "\";\n";

    sstr << "        document.getElementById(\""
         << req->getQueryParam("active")
         << "\").setAttribute(\"class\", \"active\");";

    sstr << "      }\n"
            "    }\n"
            "  xhttp.open(\"GET\", url);\n"
            "  xhttp.send();\n"
            "}\n\n";

    sstr << "navbarCssInsert();\n"
            "ajaxAndLoad(\"/navbar_"
          << "user.html\", navbarHttpInsert);\n"
                                                                          "navbarJsInsert();\n";

    file += sstr.str();

    Response* res = new Response();
    res->setHeader("Content-Type", "text/javascript");
    res->setBody(file);
    return res;
}

AddFlightHandler::AddFlightHandler(SystemInterface& si) : si_(si) {}
Response* AddFlightHandler::callback(Request* req) {
    //some code

    return Response::redirect("/home");
}

DelFlightHandler::DelFlightHandler(SystemInterface& si) : si_(si) {}
Response* DelFlightHandler::callback(Request* req) {

    try {
        //si_(req->getSessionId()).deleteFlight(id);
    }
    catch (const BadReq& ex) {
        return Response::redirect("/400");
    }
    catch (const PermissionDenied& ex) {
        return Response::redirect("/403");
    }
    catch (const NotFound& ex) {
        return Response::redirect("/404");
    }

    return Response::redirect("/home");
}

FlightMoreInfoTemplateHandler::FlightMoreInfoTemplateHandler(const std::string& filePath, SystemInterface& si)
    : TemplateHandler(filePath),
      si_(si) {}
void FlightMoreInfoTemplateHandler::setRecipe(Recipe* recipe) { recipe_ = recipe; }
std::map<std::string, std::string> FlightMoreInfoTemplateHandler::handle(Request* req) {
    std::map<std::string, std::string> context;

    std::ostringstream sstr;
    // some code
    return context;
}
FlightMoreInfoHandler::FlightMoreInfoHandler(SystemInterface& si, const std::string& filePath)
    : t_(filePath, si),
      si_(si) {}
Response* FlightMoreInfoHandler::callback(Request* req) {
    std::string idText = req->getQueryParam("id");
    if (idText.empty()) {
        return Response::redirect("/400");
    }

    int id;
    try {
        id = std::stoi(idText);
    }
    catch (...) {
        return Response::redirect("/400");
    }

    Flight* f;
    try {
        //f = si_(req->getSessionId()).getFlights(id);
    }
    catch (const BadReq& ex) {
        return Response::redirect("/400");
    }
    catch (const PermissionDenied& ex) {
        return Response::redirect("/403");
    }
    catch (const NotFound& ex) {
        return Response::redirect("/404");
    }

    //t_.setRecipe(f);
    return t_.callback(req);
}

FilterHandler::FilterHandler(SystemInterface& si) : si_(si) {}
Response* FilterHandler::callback(Request* req) {
    std::string tag = req->getBodyParam("tag");
    std::string minutesToReadyMin = req->getBodyParam("minutesToReadyMin");
    std::string minutesToReadyMax = req->getBodyParam("minutesToReadyMax");
    std::string ratingMin = req->getBodyParam("ratingMin");
    std::string ratingMax = req->getBodyParam("ratingMax");
    std::string vegetarian = req->getBodyParam("vegetarian");
    trim(tag);

    bool vegetar = (vegetarian == "on") ? true : false;
    int mtrMin, mtrMax;
    float rMin, rMax;
    try {
        mtrMin = std::stoi(minutesToReadyMin);
        mtrMax = std::stoi(minutesToReadyMax);
        rMin = std::stof(ratingMin);
        rMax = std::stof(ratingMax);
    }
    catch (...) {
        return Response::redirect("/400");
    }

    std::string sid = req->getSessionId();
    try {
        si_(sid).deleteFilters();
    }
    catch (const BadReq& ex) {
        return Response::redirect("/400");
    }
    catch (const PermissionDenied& ex) {
        return Response::redirect("/403");
    }
    catch (const NotFound& ex) {
        return Response::redirect("/404");
    }

    return Response::redirect("/home");
}

DelFiltersHandler::DelFiltersHandler(SystemInterface& si) : si_(si) {}
Response* DelFiltersHandler::callback(Request* req) {
    try {
        si_(req->getSessionId()).deleteFilters();
    }
    catch (const BadReq& ex) {
        return Response::redirect("/400");
    }
    catch (const PermissionDenied& ex) {
        return Response::redirect("/403");
    }
    catch (const NotFound& ex) {
        return Response::redirect("/404");
    }

    return Response::redirect("/home");
}

GetFiltersHandler::GetFiltersHandler(SystemInterface& si) : si_(si) {}
Response* GetFiltersHandler::callback(Request* req) {

    std::ostringstream sstr;

    Response* res = new Response();
    res->setHeader("Content-Type", "text/javascript");
    res->setBody(sstr.str());
    return res;
}

ShowFileJs::ShowFileJs(const std::string& path) : path_(path) {}
Response* ShowFileJs::callback(Request* req) {
    Response* res = new Response();
    res->setHeader("Content-Type", "text/javascript");
    res->setBody(readFile(path_.c_str()));
    return res;
}