CFLAGS+=-O0 -g
CFLAGS+=$(shell pkg-config pkg-config --cflags x11)
LDLIBS+=$(shell pkg-config pkg-config --libs x11)
LDLIBS+=-L. -lwgpu
#LDLIBS+=-L. -lwgpu-release

all: main

main: main.o

clean:
	rm -f *.o main
