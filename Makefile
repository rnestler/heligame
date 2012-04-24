CC=gcc
BIN=heligame
OBJ=Source/main.o Source/heli.o Source/backendPC.o
LIBS=sdl
CFLAGS = `pkg-config --cflags --libs $(LIBS)` -Wall -IIncludes


all: $(BIN)


$(BIN): $(OBJ)
	$(CC) -o $(BIN) -Dbackend=PC -Dmain=SDL_main $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm $(OBJ)
	rm $(BIN)
