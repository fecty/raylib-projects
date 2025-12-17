# For Reference
# 	g++ -std=c++17 main.cpp -o main.out -I../../include -L../../lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
# -isystem ../../include instead of -I../../include to disable third-party warnings.
.PHONY: clear clean

CC := g++
CC_FLAGS := -std=c++17 -isystem ../../include -L../../lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CC_OTHER_FLAGS := -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -O0 -g
BIN_DIR := bin
SOURCE := main
OTHER_SOURCES := triangle.cpp

all: clear build-test


${BIN_DIR}/${SOURCE}.out: ${SOURCE}.cpp ${BIN_DIR} 
	@echo "Building ${BIN_DIR}/${SOURCE}.out"
	@${CC} ${SOURCE}.cpp ${OTHER_SOURCES} -o ${BIN_DIR}/${SOURCE}.out ${CC_FLAGS} ${CC_OTHER_FLAGS}


test: ${BIN_DIR}/${SOURCE}.out ${BIN_DIR} 
	./${BIN_DIR}/${SOURCE}.out

build-test: ${BIN_DIR}/${SOURCE}.out ${BIN_DIR}
	@${CC} ${SOURCE}.cpp ${OTHER_SOURCES} -o ${BIN_DIR}/${SOURCE}.out ${CC_FLAGS} ${CC_OTHER_FLAGS}
	./${BIN_DIR}/${SOURCE}.out



${BIN_DIR}:
	mkdir ${BIN_DIR}

${OTHER_SOURCES}:
	echo "build"


clear:
	clear

clean:
	rm -rf ${BIN_DIR}/*.out

