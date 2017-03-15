# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif

all: pathfinder actorconnections extension 



# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o ActorEdge.o ActorNode.o ActorYear.o 
actorconnections: ActorGraph.o ActorEdge.o ActorNode.o ActorYear.o UnionFind.o Timer.o 
extension: ExtensionActorGraph.o

# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers
# add UnionFind.hpp later
ActorGraph.o: UnionFind.o ActorNode.o ActorEdge.o ActorYear.o ActorGraph.h
ActorEdge.o: ActorEdge.h 
ActorNode.o: ActorNode.h 
ActorYear.o: ActorYear.h
UnionFind.o: UnionFind.h
Timer.o: Timer.h
ExtensionActorGraph.o: ExtensionActorGraph.h
clean:
	rm -f pathfinder *.o core*

