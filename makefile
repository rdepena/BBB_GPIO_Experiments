CC ?= cc
CFLAGS =-g -Wall -Ideps -Wextra
SOURCES = src/bbgpio.c
OBJECTS = $(SOURCES:.c=.o)
DEBUGGER=lldb
SYNCTOOL=rsync
SYNCFLAGS = -rav * debian@192.168.2.2
BBBFOLDER =/home/debian/gpio_lib/
PREFIX ?= /usr/local
LINUXPREFIX ?= /usr

all:build/bbgpio.o

install: all
	ln -f build/bbgpio.o $(LINUXPREFIX)/lib/bbgpio.o
	ln -f src/bbgpio.h $(LINUXPREFIX)/include/bbgpio.h

uninstall:
	rm -f $(LINUXPREFIX)/lib/bbgpio.o
	rm -f $(LINUXPREFIX)/include/bbgpio.h

build/bbgpio.o: $(OBJECTS)
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
