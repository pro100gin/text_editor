.PHONY: prepare clean $(SUBDIRS)

vpath %.c src:lib
vpath %.h include
vpath %.o src:lib

SUBDIRS = lib src
OBJECTS = init.o read_file.o main.o

CFLAGS = -O2 -Wall -pedantic -ansi
LDFLAGS = -l ncurses


all: prepare $(OBJECTS)
		gcc -o of $(OBJECTS) $(CFLAGS) $(LDFLAGS) -g

prepare: $(SUBDIRS)
$(SUBDIRS):
		make -C $@

src: lib

clean:
		clear
		rm -rf *.o of
