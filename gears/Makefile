CC=gcc
CFLAGS=-Wall
LDFLAGS=-lGL -lGLU -lglut -lm

CFILES=$(wildcard *.c)
LDFILES=$(CFILES:%.c=%)

all: $(LDFILES)

clean:
	find . -perm +100 -type f -delete

%: %.c
