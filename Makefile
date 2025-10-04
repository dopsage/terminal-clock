
build: Vector2.o Plane.o Clock.o Main.o
	### Create executable and clean up
	g++ Vector2.o Plane.o Clock.o Main.o -o clock
	rm Vector2.o Plane.o Clock.o Main.o
	### Move the executable to 'bin' directory
	mkdir -p bin
	mv clock bin/

Vector2.o: src/Vector2.cpp
	### Compile 'Vector2' module
	g++ -c src/Vector2.cpp -I include/ -o Vector2.o

Plane.o: src/Plane.cpp
	### Compile 'Plane' module
	g++ -c src/Plane.cpp -I include/ -o Plane.o

Clock.o: src/Clock.cpp
	### Compile 'Clock' module
	g++ -c src/Clock.cpp -I include/ -o Clock.o

Main.o: src/Main.cpp
	### Compile 'Main' module
	g++ -c src/Main.cpp -I include -o Main.o
