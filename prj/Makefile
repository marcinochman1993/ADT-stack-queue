all: src/main.cpp obj/Timer.o
	g++ -std=c++11 -g -Iinc src/main.cpp obj/Timer.o -o map
	
obj/Timer.o: inc/Timer.hpp src/Timer.cpp
	g++ -c -std=c++11 -g -Iinc src/Timer.cpp -o obj/Timer.o

clean:
	rm -rf obj/* map