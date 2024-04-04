# CMPT201-X02L  

CC=gcc
CFLAGS=-Wall -g -std=c11 
LDFLAGS=-lm -lc -lncurses -ltinfo


TARGET=skyfall

OBJS= player.o main.o blocks.o leaderboard.o map.o

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ 
	
main.o: main.c 
	$(CC) $(CFLAGS) -c $<

map.o: map.c  map.h 
	$(CC) $(CFLAGS) -c $<

player.o: player.c  player.h 
	$(CC) $(CFLAGS) -c $<


blocks.o: blocks.c blocks.h
	$(CC) $(CFLAGS) -c $<

Debug: $(OBJ) 
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean Debugger valgrind

clean:
	rm -f $(TARGET) $(OBJS) Debug

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all  ./$(TARGET)

Debugger:
	gdb Debug

