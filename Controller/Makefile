MongoDB_IFLAG = -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0

jobPool.o: jobPool.cpp
	g++ -c -std=c++11 -g $^ $(pkg-config --cflags --libs libmongocxx) $(MongoDB_IFLAG)