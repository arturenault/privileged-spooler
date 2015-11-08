.PHONY: default
default: build

CXX			= clang++
CC			= clang++
CXXFLAGS	= -g -Wall --std=c++11 $(INCLUDES)
LDFLAGS		= -g
LDLIBS		= -lboost_system -lboost_filesystem 
SRC_FILES = $(shell find . -type f \( -name "*.cc" -or -name "*.h" \))

build: addqueue showqueue

addqueue: addqueue.o spooler.o

showqueue: showqueue.o spooler.o

addqueue.o: addqueue.cc spooler.h

shoqueue.o: showqueue.cc spooler.h

spooler.o: spooler.cc spooler.h

.PHONY: clean
clean:
	rm -f *.o addqueue showqueue

.PHONY: format
format:
	for file in $(SRC_FILES) ; do \
		clang-format --style=Google -i $$file ; \
	done

.PHONY: all
all: clean default
