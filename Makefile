#!make -f

CXX=clang++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp DetectNegativeCycle.cpp DetectCycle.cpp IsBipartite.cpp IsConnected.cpp ShortestPath.cpp
TESTSOURCES=TestCounter.cpp Test.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TESTOBJECTS=$(TESTSOURCES:.cpp=.o)

run: demo
	./demo

runtests: test
	./test

demo: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test


# *********** dont delete this**************
# SOURCES=Graph.cpp Algorithms.cpp  DetectNegativeCycle.cpp  DetectCycle.cpp IsBipartite.cpp IsConnected.cpp ShortestPath.cpp GraphProperties.hpp

