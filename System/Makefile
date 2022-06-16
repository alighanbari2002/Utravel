#---------------------------------------------------------------------------------------------------------------------------------
PATH_OBJ     = ./obj
PATH_SRC     = ./Src
PATH_EXC     = ./Exception
PATH_FIL     = ./Filter
#---------------------------------------------------------------------------------------------------------------------------------
RM           = @rm -rf
MKDIR        = @mkdir -p
#---------------------------------------------------------------------------------------------------------------------------------
CXX          = g++
CPPFLAGS     = -std=c++11
CC           = $(CXX) $(CXXFLAGS)
#---------------------------------------------------------------------------------------------------------------------------------
OUT_EXE      = utravel.out
#---------------------------------------------------------------------------------------------------------------------------------
FILES_NAME   = $(PATH_OBJ)/main.o $(PATH_OBJ)/Utravel.o $(PATH_OBJ)/System.o $(PATH_OBJ)/Flight.o $(PATH_OBJ)/Cflight.o $(PATH_OBJ)/Ticket.o $(PATH_OBJ)/Time.o $(PATH_OBJ)/Functions.o $(PATH_OBJ)/Utils.o $(PATH_OBJ)/User.o
FILES_FILTER = $(PATH_OBJ)/Filter_airline.o $(PATH_OBJ)/Filter_cost.o $(PATH_OBJ)/Filter_from.o $(PATH_OBJ)/Filter_time.o

HPP_EXC      = $(PATH_EXC)/Bad_req.hpp $(PATH_EXC)/Not_found.hpp $(PATH_EXC)/Permission_denied.hpp
HPP_FILTER   = $(PATH_FIL)/Filter_airline.hpp $(PATH_FIL)/Filter_cost.hpp $(PATH_FIL)/Filter_from.hpp $(PATH_FIL)/Filter_time.hpp
#---------------------------------------------------------------------------------------------------------------------------------
all: pre_build build


pre_build:
	$(MKDIR) $(PATH_OBJ)

build: $(FILES_NAME) $(FILES_FILTER)
	$(CC) $(FILES_NAME) $(FILES_FILTER) -o $(OUT_EXE)
#---------------------------------------------------------------------------------------------------------------------------------
$(PATH_OBJ)/Utravel.o: $(PATH_SRC)/Utravel.hpp $(PATH_SRC)/System.hpp $(PATH_SRC)/User.hpp $(PATH_SRC)/Functions.hpp $(PATH_SRC)/Utils.hpp $(HPP_EXC) $(PATH_SRC)/Utravel.cpp
	$(CC) -c $(PATH_SRC)/Utravel.cpp -o $(PATH_OBJ)/Utravel.o

$(PATH_OBJ)/System.o: $(PATH_SRC)/System.hpp $(PATH_SRC)/Flight.hpp $(PATH_SRC)/User.hpp $(PATH_SRC)/Utils.hpp $(PATH_SRC)/Ticket.hpp $(PATH_SRC)/Functions.hpp $(PATH_SRC)/Cflight.hpp $(HPP_EXC) $(HPP_FILTER) $(PATH_SRC)/System.cpp
	$(CC) -c $(PATH_SRC)/System.cpp -o $(PATH_OBJ)/System.o

$(PATH_OBJ)/Flight.o: $(PATH_SRC)/Flight.hpp $(PATH_SRC)/Time.hpp $(PATH_SRC)/Functions.hpp $(PATH_SRC)/Utils.hpp $(PATH_SRC)/Flight.cpp
	$(CC) -c $(PATH_SRC)/Flight.cpp -o $(PATH_OBJ)/Flight.o

$(PATH_OBJ)/Cflight.o: $(PATH_SRC)/Cflight.hpp $(PATH_SRC)/Time.hpp $(PATH_SRC)/Functions.hpp $(PATH_SRC)/Flight.hpp $(PATH_SRC)/Cflight.cpp 
	$(CC) -c $(PATH_SRC)/Cflight.cpp -o $(PATH_OBJ)/Cflight.o

$(PATH_OBJ)/User.o: $(PATH_SRC)/User.hpp $(PATH_SRC)/Ticket.hpp $(PATH_SRC)/Functions.hpp $(PATH_SRC)/Utils.hpp $(HPP_EXC) $(PATH_SRC)/User.cpp
	$(CC) -c $(PATH_SRC)/User.cpp -o $(PATH_OBJ)/User.o

$(PATH_OBJ)/Ticket.o: $(PATH_SRC)/Ticket.hpp $(PATH_SRC)/Flight.hpp $(PATH_SRC)/Functions.hpp $(PATH_SRC)/Ticket.cpp
	$(CC) -c $(PATH_SRC)/Ticket.cpp -o $(PATH_OBJ)/Ticket.o

$(PATH_OBJ)/main.o: $(PATH_SRC)/Utravel.hpp $(PATH_SRC)/main.cpp
	$(CC) -c $(PATH_SRC)/main.cpp -o $(PATH_OBJ)/main.o

$(PATH_OBJ)/Time.o: $(PATH_SRC)/Time.hpp $(PATH_SRC)/Time.cpp
	$(CC) -c $(PATH_SRC)/Time.cpp -o $(PATH_OBJ)/Time.o

$(PATH_OBJ)/Functions.o: $(PATH_SRC)/Functions.hpp $(PATH_SRC)/Utils.hpp $(PATH_SRC)/Functions.cpp
	$(CC) -c $(PATH_SRC)/Functions.cpp -o $(PATH_OBJ)/Functions.o

$(PATH_OBJ)/Utils.o : $(PATH_SRC)/Utils.hpp $(PATH_SRC)/Utils.cpp
	$(CC) -c $(PATH_SRC)/Utils.cpp -o $(PATH_OBJ)/Utils.o
#---------------------------------------------------------------------------------------------------------------------------------
AIRLINE = $(PATH_FIL)/Filter_airline.hpp $(PATH_FIL)/Filter.hpp $(PATH_FIL)/Filter_airline.cpp
COST    = $(PATH_FIL)/Filter_cost.hpp $(PATH_FIL)/Filter.hpp $(PATH_FIL)/Filter_cost.cpp
FROM    = $(PATH_FIL)/Filter_from.hpp $(PATH_FIL)/Filter.hpp $(PATH_FIL)/Filter_from.cpp
TIME    = $(PATH_FIL)/Filter_time.hpp $(PATH_FIL)/Filter.hpp $(PATH_FIL)/Filter_time.cpp
#---------------------------------------------------------------------------------------------------------------------------------
$(PATH_OBJ)/Filter_airline.o: $(PATH_SRC)/Flight.hpp $(AIRLINE)
	$(CC) -c $(PATH_FIL)/Filter_airline.cpp -o $(PATH_OBJ)/Filter_airline.o

$(PATH_OBJ)/Filter_cost.o: $(PATH_SRC)/Flight.hpp $(COST)
	$(CC) -c $(PATH_FIL)/Filter_cost.cpp -o $(PATH_OBJ)/Filter_cost.o

$(PATH_OBJ)/Filter_from.o: $(PATH_SRC)/Flight.hpp $(FROM)
	$(CC) -c $(PATH_FIL)/Filter_from.cpp -o $(PATH_OBJ)/Filter_from.o

$(PATH_OBJ)/Filter_time.o: $(PATH_SRC)/Flight.hpp $(TIME)
	$(CC) -c $(PATH_FIL)/Filter_time.cpp -o $(PATH_OBJ)/Filter_time.o
#---------------------------------------------------------------------------------------------------------------------------------
clean:
	$(RM) $(PATH_OBJ) $(OUT_EXE)
#---------------------------------------------------------------------------------------------------------------------------------