%.o: %.cpp
	g++ -std=c++11 -g -c $^

test-main.exe: card.o test-main.o
	g++ -std=c++11 -g $^ -o $@

clean:
	rm -rf $(wildcard *.exe) $(wildcard *.o)