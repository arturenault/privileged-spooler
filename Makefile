.PHONY: default
default: build

CXX			= clang++
CC			= clang++
CXXFLAGS	= -g -Wall --std=c++11 $(INCLUDES)
LDFLAGS		= -g
SRC_FILES = $(shell find . -type f \( -name "*.cc" -or -name "*.h" \))

build: add_queue

add_queue: add_queue.o spooler.o

add_queue.o: add_queue.cc spooler.h

spooler.o: spooler.cc spooler.h

.PHONY: clean
clean:
	rm -f *.o add_queue

.PHONY: format
format:
	for file in $(SRC_FILES) ; do \
		clang-format --style=Google -i $$file ; \
	done

.PHONY: all
all: clean default
