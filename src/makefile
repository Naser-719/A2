# CMPT201-X02L  
#Name: Mustafa Al-Hamadani, Naser Issa, Gurmehar Singh
CC=gcc
CFLAGS=-Wall -g -std=c11 
LDFLAGS=-lm -lc -lncurses -ltinfo


OUTDIR = ../bin
TARGET = $(OUTDIR)/appGame

OBJS= player.o main.o blocks.o  map.o

all: $(TARGET)


$(TARGET): $(OBJS)
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ 
	
main.o: main.c 
	$(CC) $(CFLAGS) -c $<

map.o: map.c  map.h best_time.txt
	$(CC) $(CFLAGS) -c $<

player.o: player.c  player.h 
	$(CC) $(CFLAGS) -c $<

blocks.o: blocks.c blocks.h
	$(CC) $(CFLAGS) -c $<

best_time.txt:
	echo 0 > $@

Debug: $(OBJ) 
	$(CC) $(CFLAGS) $^ -o $@



.PHONY: clean Debugger Mem_valgrind doc

clean:
	rm -f $(TARGET) $(OBJS) Debug

Mem_valgrind:
	valgrind --leak-check=full --show-leak-kinds=all  ./$(TARGET)

Debugger:
	gdb Debug

doc:
	doxygen ../doc/Doxyfile