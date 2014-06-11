all: src/main.cpp obj/PlanszaWarcaby.o obj/Wspolrzedna.o obj/PlanszaWarcaby.o obj/Warcaby.o obj/Pole.o obj/Sciezka.o \
	obj/WarcabyGUI.o obj/
	g++ -g -Iinc src/main.cpp obj/Wspolrzedna.o obj/PlanszaWarcaby.o obj/Warcaby.o \
	obj/Pole.o obj/Sciezka.o obj/WarcabyGUI.o -lSDL -lSDL_ttf -o warcaby -std=c++11

obj/WarcabyGUI.o: inc/WarcabyGUI.hpp src/WarcabyGUI.cpp obj/
	g++ -c -g -Iinc src/WarcabyGUI.cpp -o obj/WarcabyGUI.o -std=c++11

obj/Pole.o: inc/Pole.hpp src/Pole.cpp obj/
	g++ -c -g -Iinc src/Pole.cpp -o obj/Pole.o -std=c++11

obj/Warcaby.o: inc/Warcaby.hpp src/Warcaby.cpp obj/
	g++ -c -g -Iinc src/Warcaby.cpp -o obj/Warcaby.o -std=c++11

obj/PlanszaWarcaby.o: inc/PlanszaWarcaby.hpp src/PlanszaWarcaby.cpp obj/
	g++ -c -g -Iinc src/PlanszaWarcaby.cpp -o obj/PlanszaWarcaby.o -std=c++11
	
obj/Wspolrzedna.o: inc/Wspolrzedna.hpp src/Wspolrzedna.cpp obj/
	g++ -c -g -Iinc src/Wspolrzedna.cpp -o obj/Wspolrzedna.o -std=c++11
	
obj/Sciezka.o: inc/Sciezka.hpp src/Sciezka.cpp obj/
	g++ -c -g -Iinc src/Sciezka.cpp -o obj/Sciezka.o -std=c++11
	
obj/:
	mkdir obj/

clean: 
	rm -rf obj/* warcaby