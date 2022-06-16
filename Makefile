PATH_SYSTEM = .\system
PATH_SERVER = .\server

LDFLAGS  =
LDLIBS   =
ifeq ($(OS),Windows_NT)
	LDLIBS += -l Ws2_32
else
	LDLIBS += -pthread
endif

OUT_EXE  = goodeats.exe

#----------------------------------------

all: makeall

makeall:
	@echo incomplete!

clean: clean-system clean-server clean-exe

clean-system:
	$(MAKE) -C $(PATH_SYSTEM) clean

clean-server:
	$(MAKE) -C $(PATH_SERVER) clean

clean-exe:
	$(RM) $(PATH_SERVER)/bin/$(OUT_EXE)

link:
	$(CC) $(LDFLAGS) $(PATH_SERVER)/obj/*.o $(PATH_SYSTEM)/obj/*.o $(LDLIBS) -o $(PATH_SERVER)/bin/$(OUT_EXE)

run:
	cd $(PATH_SERVER)/bin && $(OUT_EXE)