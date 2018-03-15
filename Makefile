MongoDB_IFLAG = -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0
MongoDB_LFLAG = -L/usr/local/lib -lmongocxx -lbsoncxx
NCURSES_LFLAG = -lncurses

all: dependency main.exe

dependency:
	+$(MAKE) -C Modal/
	+$(MAKE) -C Service/
	+$(MAKE) -C Controller/
	+$(MAKE) -C UI/
	
main.o: main.cpp
	g++ -c -std=c++11 -g $^ $(pkg-config --cflags --libs libmongocxx) $(MongoDB_IFLAG)

ui-demo.o: ui-demo.cpp
	g++ -c -std=c++11 -g $^ $(NCURSES_LFLAG) $(pkg-config --cflags --libs libmongocxx libncurses) $(MongoDB_IFLAG)

main.exe: Modal/card.o Service/studyService.o Service/config.o Controller/jobPool.o main.o UI/ui.o
	g++ -std=c++11 -g -o $@ $^ -Wall $(pkg-config --cflags --libs libmongocxx) -Wl,-rpath,/usr/local/lib $(NCURSES_LFLAG) $(MongoDB_LFLAG)

ui-test.exe: Modal/card.o Service/studyService.o Service/config.o Controller/jobPool.o ui-demo.o UI/ui.o
	g++ -std=c++11 -g -o $@ $^ -Wall $(pkg-config --cflags --libs libmongocxx) -Wl,-rpath,/usr/local/lib $(NCURSES_LFLAG) $(MongoDB_LFLAG)

SUBDIR_ROOTS := Modal Service Controller UI
DIRS := . $(shell find $(SUBDIR_ROOTS) -type d)
GARBAGE_PATTERNS := *.o *.exe
GARBAGE := $(foreach DIR,$(DIRS),$(addprefix $(DIR)/,$(GARBAGE_PATTERNS)))

clean:
	rm -rf  $(GARBAGE)
	rm -f config.txt
