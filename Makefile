CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr
REQUIRED = anicholas.cpp etagaca.cpp jhicks.cpp jkuo.cpp jrojas.cpp

all: asteroids

asteroids: asteroids.cpp log.cpp timers.cpp $(REQUIRED)
	g++ $(CFLAGS) asteroids.cpp log.cpp timers.cpp $(REQUIRED) -I/opt/X11/include libggfonts.a -Wall -Wextra $(LFLAGS) -oasteroids

clean:
	rm -f asteroids
	rm -f *.o *.x

