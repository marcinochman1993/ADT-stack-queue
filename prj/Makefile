all: src/main.cpp obj/Timer.o obj/StringHash.o obj/HashTableGetProblem.o obj/PairSD.o \
	obj/MapGetProblem.o obj/BinarySTGetProblem.o
	g++ -std=c++11 -g -Iinc src/main.cpp obj/Timer.o obj/StringHash.o \
	obj/HashTableGetProblem.o obj/PairSD.o obj/MapGetProblem.o \
	obj/BinarySTGetProblem.o -o simplex
	
obj/StringHash.o: src/StringHash.cpp inc/StringHash.hpp obj/
	g++ -c -std=c++11 -g -Iinc src/StringHash.cpp -o obj/StringHash.o
	
obj/HashTableGetProblem.o: src/HashTableGetProblem.cpp inc/HashTableGetProblem.hpp obj/
	g++ -c -std=c++11 -g -Iinc src/HashTableGetProblem.cpp -o obj/HashTableGetProblem.o
	
obj/MapGetProblem.o: src/MapGetProblem.cpp inc/MapGetProblem.hpp obj/
	g++ -c -std=c++11 -g -Iinc src/MapGetProblem.cpp -o obj/MapGetProblem.o
	
obj/BinarySTGetProblem.o: src/BinarySTGetProblem.cpp inc/BinarySTGetProblem.hpp obj/
	g++ -c -std=c++11 -g -Iinc src/BinarySTGetProblem.cpp -o obj/BinarySTGetProblem.o

obj/Timer.o: inc/Timer.hpp src/Timer.cpp obj/
	g++ -c -std=c++11 -g -Iinc src/Timer.cpp -o obj/Timer.o
	
obj/PairSD.o: inc/PairSD.hpp src/PairSD.cpp obj/
	g++ -c -std=c++11 -g -Iinc src/PairSD.cpp -o obj/PairSD.o

obj/:
	mkdir obj/
clean:
	rm -rf obj simplex