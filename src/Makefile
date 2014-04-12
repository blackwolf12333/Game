NAME = game

CFLAGS = -c -std=c99 -Wall -Wextra

LDFLAGS = -lSDL -lSDL_image -lGL -lGLU

all: Main.o Graphics.o World.o WorldLoader.o
	$(CC) Main.o Graphics.o World.o WorldLoader.o $(LDFLAGS) -o $(NAME)

WorldLoader.o: WorldLoader.c WorldLoader.h
	$(CC) $(CFLAGS) WorldLoader.c

World.o: World.c World.h WorldLoader.h
	$(CC) $(CFLAGS) World.c

Graphics.o: Graphics.c Graphics.h
	$(CC) $(CFLAGS) Graphics.c

Main.o: Main.c
	$(CC) $(CFLAGS) Main.c

clean:
	rm -f *.o
	rm -f $(NAME)

re: clean all
