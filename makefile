CC ?= cc
CFLAGS =-g -Wall -Ideps -Wextra
SOURCES = src/bbbgpio.c
OBJECTS = $(SOURCES:.c=.o)
DEBUGGER=lldb
SYNCTOOL=rsync
SYNCFLAGS = -rav * root@192.168.7.2
BBBFOLDER =/home/debian/gpio_lib/
PREFIX ?= /usr/local
LINUXPREFIX ?= /usr

all:build/bbbgpio.o

install: all
	ln -f build/bbbgpio.o $(LINUXPREFIX)/lib/bbbgpio.o
	ln -f src/bbbgpio.h $(LINUXPREFIX)/include/bbbgpio.h

uninstall:
	rm -f $(LINUXPREFIX)/lib/bbbgpio.o
	rm -f $(LINUXPREFIX)/include/bbbgpio.h

build/bbbgpio.o: $(OBJECTS)
	@mkdir -p build
	cp $^ $@

bin/test: test.o $(OBJECTS)
	@mkdir -p bin
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm -fr bin build *.o src/*.o

test: bin/test
	echo @./$<
	@./$<

debug: bin/test
	$(DEBUGGER) $<

deploy:all
	$(SYNCTOOL) $(SYNCFLAGS):$(BBBFOLDER)

.PHONY: test clean deploy
