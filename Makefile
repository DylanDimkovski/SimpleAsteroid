CPPFLAGS=-Wall -g
OBJECTS=main.o ship.o renderer.o arena.o asteroid.o game.o bullet.o
TARGET=Asteroid
%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $@ $<
$(TARGET): $(OBJECTS)
	g++ $(OBJECTS) -o $(TARGET) -g -lglut -lGL
main.o: main.cpp renderer.h keys.h arena.h settings.h game.h
ship.o: ship.cpp ship.h keys.h move.h renderer.h vector.h
renderer.o: renderer.cpp renderer.h move.h ship.h asteroid.h
arena.o: arena.cpp arena.h renderer.h settings.h vector.h ship.h
asteroid.o: asteroid.cpp asteroid.h keys.h vector.h renderer.h
game.o: game.cpp game.h asteroid.h settings.h
bullet.o: bullet.cpp bullet.h renderer.h

clean:
	$(RM) Asteroid *.o
