.PHONY: default
default: build

CXX			= clang++
CC			= clang++
CXXFLAGS	= -g -Wall --std=c++11 $(INCLUDES)
LDFLAGS		= -g
LDLIBS		= -lboost_system -lboost_filesystem 
SRC_FILES	= $(shell find . -type f \( -name "*.cc" -or -name "*.h" \))
USER_ID		= $(shell id -u)
ROOT_DIR	= /spool
_ROOT_DIR	= \"$(ROOT_DIR)\"
INCLUDES	= -DROOT_DIR=$(_ROOT_DIR)

check:
ifneq ($(USER_ID), 0)
	$(error Please run as root)
endif

compile: check addqueue showqueue rmqueue
	
build: compile
	chmod u+s addqueue showqueue rmqueue
	mv addqueue /usr/local/bin
	mv showqueue /usr/local/bin
	mv rmqueue /usr/local/bin

addqueue: addqueue.o spooler.o

showqueue: showqueue.o spooler.o

rmqueue: rmqueue.o spooler.o

.PHONY: clean
clean: check
	rm -rf *.o addqueue showqueue rmqueue /usr/local/bin/addqueue /usr/local/bin/showqueue /usr/local/bin/rmqueue $(ROOT_DIR)

.PHONY: format
format:
	for file in $(SRC_FILES) ; do \
		clang-format --style=Google -i $$file ; \
	done

.PHONY: all
all: clean default
