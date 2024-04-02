# CMPT201-X02L  

CC=gcc
CFLAGS=-Wall -g -std=c11 -lm -lc -lncurses -ltinfo

TARGET=skyfall

OBJS=npc.o

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ 
	
skyfall: skyfall.c skyfall.h
	$(CC) $(CFLAGS) -c $<

npc.o: npc.c  npc.h 
	$(CC) $(CFLAGS) -c $<

blocks.o: blocks.c blocks.h
	$(CC) $(CFLAGS) -c $<

Debug: $(OBJ) 
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean Debugger

clean:
	rm -f $(TARGET) $(OBJS) Debug

Debugger:
	gdb Debug

