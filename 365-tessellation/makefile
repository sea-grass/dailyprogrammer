.PHONY: clean
default: all

all: tessellate

tessellate: src/main.c
	$(CC) -std=c99 -Wall -g -o $@ $^

clean:
	rm -rf tessellate
