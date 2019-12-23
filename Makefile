CC := g++
FILE := main.cpp
OBJ := main

.PHONY: all compile run

all: compile

compile:
	@echo "Compiling ${FILE}... "
	${CC} -std=c++1z -Wall -pedantic ${FILE} -o ${OBJ}

run:
	./${OBJ}

clean:
	@echo "Removing ${OBJ}"
	rm ${OBJ}