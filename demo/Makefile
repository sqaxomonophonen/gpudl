LDLIBS+=-lX11 -lm
CFLAGS+=-Wall
CFLAGS+=-I.. -I.
all: demo
demo.o: demo.c ../gpudl.h
gpudl.o: gpudl.c ../gpudl.h
demo: demo.o gpudl.o
clean:
	rm -f *.o demo
cleandeps:
	rm -f libwgpu_native.so webgpu.h wgpu.h
