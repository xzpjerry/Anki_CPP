MongoDB_IFLAG = -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0
MongoDB_LFLAG = -L/usr/local/lib -lmongocxx -lbsoncxx

jobPool.o: jobPool.cpp
	g++ -c -std=c++11 -g $^ $(MongoDB_IFLAG)