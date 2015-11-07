CC ?= cc
AR ?= AR
CFLAGS =-g -std=c99 -Wall
SOURCES = src/bbbgpio.c
OBJECTS = $(SOURCES:.c=.o)
DEBUGGER=lldb
SYNCTOOL=rsync
SYNCFLAGS = -rav * root@192.168.1.202
BBBFOLDER =/home/root/gpio_lib/

all:build/bbbgpio.a

build/bbbgpio.a: $(OBJECTS)
	@mkdir -p build
	$(AR) rcs $@ $^

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
