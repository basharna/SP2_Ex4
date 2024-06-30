CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -O3

SRC = demo.cpp
OBJ = $(SRC:.cpp=.o)
HEADERS = tree.hpp tree.tpp
DEPS = $(HEADERS)
EXEC = demo
TEST_EXEC = test

all: $(EXEC) $(TEST_EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_EXEC): test.o $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $<

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(EXEC) $(OBJ) $(TEST_EXEC) *.o

.PHONY: all clean
