CC = gcc
CFLAGS = -O0 -I../include -I../c-libp2p/include -I../c-multihash/include -Wall

ifdef DEBUG
CFLAGS += -g3
endif

LFLAGS = 
DEPS = 
OBJS = multibase.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJS)

clean:
	rm -f *.o
