MongoDB_IFLAG = -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0
MongoDB_LFLAG = -L/usr/local/lib -lmongocxx -lbsoncxx

all: dependency main.exe

dependency:
	+$(MAKE) -C Modal/
	+$(MAKE) -C Controller/
	
main.o: main.cpp
	g++ -c -std=c++11 -g $^ $(MongoDB_IFLAG)

main.exe: Modal/card.o Controller/jobPool.o main.o
	g++ -std=c++11 -g -o $@ $^ -Wall $(MongoDB_LFLAG)

clean:
	rm -rf $(wildcard *.exe) $(wildcard *.o)