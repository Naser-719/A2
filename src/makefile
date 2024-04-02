# CMPT201-X02L  

CC=gcc
CFLAGS=-Wall -g -std=c11 -lm -lc -lncurses -ltinfo

TARGET=skyfall

OBJS= player.o main.o blocks.o leaderboard.o map.o

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ 
	
main.o: main.c 
	$(CC) $(CFLAGS) -c $<

map.o: map.c  map.h 
	$(CC) $(CFLAGS) -c $<

player.o: player.c  player.h 
	$(CC) $(CFLAGS) -c $<

leaderboard.o: leaderboard.c  leaderboard.h 
	$(CC) $(CFLAGS) -c $<

blocks.o: blocks.c blocks.h
	$(CC) $(CFLAGS) -c $<


# blocks_test: blocks.o test_blocks.c
# 	$(CC) $(CFLAGS) test_blocks.c blocks.o -o blocks_test


Debug: $(OBJ) 
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean Debugger

clean:
	rm -f $(TARGET) $(OBJS) Debug

Debugger:
	gdb Debug

