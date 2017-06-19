.PHONY: prepare clean $(SUBDIRS)

vpath %.c src:lib
vpath %.h include
vpath %.o src:lib

SUBDIRS = lib src
OBJECTS = init.o readData.o main.o

CFLAGS = -std=c99
LDFLAGS = -l ncurses


all: prepare $(OBJECTS)
		gcc -o fm $(OBJECTS) $(CFLAGS) $(LDFLAGS)

prepare: $(SUBDIRS)
$(SUBDIRS):
		make -C $@

src: lib

clean:
		rm -rf *.o fm
