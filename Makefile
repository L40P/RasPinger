.DEFAULT_GOAL = all
.PHONY = all compile clean

OUT = RasPinger.out
CC = g++
CFLAGS = -Wall
LIBS = -lwiringPi -lpthread

_FILES = config.cpp config.h dat.cpp dat.h files.cpp files.h ips.cpp ips.h log.cpp log.h
FILES = ${_FILES:%=files/%}
_GPIO = gpio.cpp gpio.h
GPIO = ${_GPIO:%=gpio/%}
_PING = ping.cpp ping.h threading.cpp threading.h
PING = ${_PING:%=ping/%}
SRCS = ${FILES} ${GPIO} ${PING} main.cpp

all: compile

compile:
	${CC} -o ${OUT} ${CFLAGS} ${LIBS} ${SRCS}

clean:
	rm -f ${OUT}
