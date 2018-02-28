
all: mongoDB_test.o test.exe
mongoDB_test.o: mongoDB_test.cpp
	g++ -c --std=c++11 mongoDB_test.cpp

test.exe: mongoDB_test.o
	g++ --std=c++11 -o test.exe mongoDB_test.o -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 \
  		-I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 \
  		-L/usr/local/lib -lmongocxx -lbsoncxx