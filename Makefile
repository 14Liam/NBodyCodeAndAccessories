CC=g++
# CPPFLAGS=-g $(shell root-config --cflags)
CPPFLAGS=-std=c++11 -I../lib/root/include -I../lib/ginac/include
# LDFLAGS=-g $(shell root-config --ldflags)
LDFLAGS=-Wl,-rpath,'$$ORIGIN/../lib/root/lib' -Wl,-rpath,'$$ORIGIN/../lib/ginac/lib'
# LDLIBS=$(shell root-config --libs)
LDLIBS=-L../lib/ginac/lib -lcln -lginac -L../lib/root/lib -lGui -lCore -lRIO -lHist -lGraf -lGpad -lRint -lMatrix -lMathCore -lThread -pthread -lm -ldl

SRCS = $(wildcard *.cpp)

PROGS = $(patsubst %.cpp,%,$(SRCS))

all: $(PROGS)

# all:
# 	g++ main.cpp -lcln -lginac -L/usr/lib64/root -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic -std=c++14 -o comp.o -I/usr/include/root

# g++ -std=c++14 -I../../../libraries/libs/root/include -I../../../libraries/libs/ginac/include main.cpp -Wl,-rpath,'$$ORIGIN/../../../libraries/libs/root/lib' -Wl,-rpath,'$$ORIGIN/../../../libraries/libs/ginac/lib' -L../../../libraries/libs/ginac/lib -lcln -lginac -L../../../libraries/libs/root/lib -pthread -lm -ldl

# g++ main.cpp -std=c++14 -I../../../libraries/libs/root/include -I../../../libraries/libs/ginac/include -L../../../libraries/libs/ginac/lib -lcln -lginac -L../../../libraries/libs/root/lib -lGui -lCore -lRIO -lThread -lGpad -lGraf -lMathCore
