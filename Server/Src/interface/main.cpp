#include <iostream>

#include "../server/server.hpp"
#include "handlers.hpp"
#include "system_interface.hpp"

constexpr int PORT = 5000;

int main(int argc, char* argv[]) {
    try {
        SystemInterface sysInterface;
        sysInterface.recieve_flights(argc, argv);
        Server server(PORT);
        server.setNotFoundErrPage("static/err/404.html");

        server.get("/"        , new CasHandler(sysInterface, "static/cas/cas.html"));
        server.get("/cas.css" , new ShowPage("static/cas/cas.css"));
        server.get("/cas_background.jpg", new ShowImage("static/cas/cas_background.jpg"));
        server.get("/logo.png", new ShowImage("static/common/logo.png"));

        server.post("/login" , new LoginHandler(sysInterface));
        server.post("/signup", new SignupHandler(sysInterface));
        server.post("/logout", new LogoutHandler(sysInterface));

        server.get("/home"     , new HomepageHandler(sysInterface, "static/home/home_user.html"));
        server.get("/home.css" , new ShowPage("static/home/home.css"));
        server.get("/home.js"  , new HomepageJsHandler(sysInterface));
        server.get("/Flight.js", new ShowFileJs("static/home/Flight.js"));

        server.get("/Flight"   , new FlightMoreInfoHandler(sysInterface, "template/Flight_moreinfo.html"));
        server.get("/Flight_moreinfo.css", new ShowPage("template/Flight_moreinfo.css"));

        server.post("/filter"  , new FilterHandler(sysInterface));
        server.post("/delfilters"  , new DelFiltersHandler(sysInterface));
        server.get("/filter.js", new GetFiltersHandler(sysInterface));

        server.get("/addFlight" , new ShowPage("static/addFlight.html"));
        server.get("/addFlight.css" , new ShowPage("static/addFlight.css"));
        server.post("/addFlight", new AddFlightHandler(sysInterface));
        server.post("/delFlight", new DelFlightHandler(sysInterface));

        server.get("/404", new ShowPage("static/err/404.html"));
        server.get("/403", new ShowPage("static/err/403.html"));
        server.get("/401", new ShowPage("static/err/401.html"));
        server.get("/400", new ShowPage("static/err/400.html"));
        server.get("/err.css" , new ShowPage("static/err/err.css"));

        server.get("/favicon.ico"      , new ShowImage("static/common/favicon.ico"));
        server.get("/common.css"       , new ShowPage("static/common/common.css"));
        server.get("/common_inputs.css", new ShowPage("static/common/common_inputs.css"));
        server.get("/btn_future.css"   , new ShowPage("static/common/btn_future.css"));

        server.run();
    }
    catch (Server::Exception& e) {
        std::cerr << e.getMessage() << std::endl;
    }
}