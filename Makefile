CC=gcc
BIN=heligame
OBJ=Source/main.o Source/game.o Source/heli.o Source/backendPC.o Source/wall.o Source/landscape.o
LIBS=sdl SDL_ttf
CFLAGS = `pkg-config --cflags --libs $(LIBS)` -Wall -IIncludes -DBACKENDPC=1  -std=c99 -DDEBUG -g


all: $(BIN)


$(BIN): $(OBJ)
	$(CC) -o $(BIN) -Dmain=SDL_main $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm $(OBJ)
	rm $(BIN)

run: $(BIN)
	./$(BIN)

debug: $(BIN)
	gdb ./$(BIN)
