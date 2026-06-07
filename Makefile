CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic
EXEFILE = program
INCLUDE = include
SRC = src

SOURCES = $(wildcard $(SRC)/*.cpp)

all: $(EXEFILE)

$(EXEFILE): $(SOURCES)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) $(SRC)/* -o $(EXEFILE)

run: $(EXEFILE)
	./$(EXEFILE)

clean:
	rm -f *.o $(EXEFILE)

.PHONY: all run clean