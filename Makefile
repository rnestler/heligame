CC=gcc
BIN=heligame
OBJ=Source/main.o Source/heli.o Source/backendPC.o Source/wall.o Source/landscape.o
LIBS=sdl
CFLAGS = `pkg-config --cflags --libs $(LIBS)` -Wall -IIncludes -DBACKENDPC=1 


all: $(BIN)


$(BIN): $(OBJ)
	$(CC) -o $(BIN) -Dmain=SDL_main $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm $(OBJ)
	rm $(BIN)
