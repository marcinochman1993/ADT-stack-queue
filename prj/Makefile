all: src/main.cpp inc/Vector.hpp inc/VStack.hpp inc/LStack.hpp obj/Timer.o obj/LQueueAddProblem.o \
 obj/VQueueDoubleAddProblem.o obj/VQueueIncAddProblem.o obj/LStackAddProblem.o obj/VStackDoubleAddProblem.o \
 obj/VStackIncAddProblem.o  
	g++ src/main.cpp obj/Timer.o obj/LQueueAddProblem.o obj/VQueueDoubleAddProblem.o \
	obj/LStackAddProblem.o obj/VStackDoubleAddProblem.o  obj/VStackIncAddProblem.o \
	obj/VQueueIncAddProblem.o -Iinc -std=c++11 -g -o ADT 
	
obj/Timer.o: inc/Timer.hpp src/Timer.cpp
	g++ -c src/Timer.cpp -Iinc -g -std=c++11 -o obj/Timer.o
	
obj/LQueueAddProblem.o: inc/LQueueAddProblem.hpp src/LQueueAddProblem.cpp
	g++ -c src/LQueueAddProblem.cpp -Iinc -g -std=c++11 -o obj/LQueueAddProblem.o

obj/VQueueDoubleAddProblem.o: inc/VQueueDoubleAddProblem.hpp src/VQueueDoubleAddProblem.cpp
	g++ -c src/VQueueDoubleAddProblem.cpp -Iinc -g -std=c++11 -o obj/VQueueDoubleAddProblem.o
	
obj/VQueueIncAddProblem.o: inc/VQueueIncAddProblem.hpp src/VQueueIncAddProblem.cpp
	g++ -c src/VQueueIncAddProblem.cpp -Iinc -g -std=c++11 -o obj/VQueueIncAddProblem.o

obj/LStackAddProblem.o: inc/LStackAddProblem.hpp src/LStackAddProblem.cpp
	g++ -c src/LStackAddProblem.cpp -Iinc -g -std=c++11 -o obj/LStackAddProblem.o
	
obj/VStackDoubleAddProblem.o: inc/VStackDoubleAddProblem.hpp src/VStackDoubleAddProblem.cpp
	g++ -c src/VStackDoubleAddProblem.cpp -Iinc -g -std=c++11 -o obj/VStackDoubleAddProblem.o	

obj/VStackIncAddProblem.o: inc/VStackIncAddProblem.hpp src/VStackIncAddProblem.cpp
	g++ -c src/VStackIncAddProblem.cpp -Iinc -g -std=c++11 -o obj/VStackIncAddProblem.o

graphs: 
	Rscript tools/generateGraphs.R
	
clean:
	rm -rf obj/* ADT wyniki/*