CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr
REQUIRED = anicholas.cpp etagaca.cpp jhicks.cpp jkuo.cpp jrojas.cpp Global.cpp

all: maze

maze: asteroids.cpp log.cpp timers.cpp $(REQUIRED)
	g++ $(CFLAGS) asteroids.cpp log.cpp timers.cpp $(REQUIRED) libggfonts.a -Wall -Wextra $(LFLAGS) -omaze

clean:
	rm -f maze
	rm -f *.o *.x

