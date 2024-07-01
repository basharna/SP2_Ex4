
# ID: 212487144
# Email: nbashar4@gmail.com


CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -O3 -g

# Include path for SFML headers
INCLUDES = -I/usr/local/include

# Libraries to link against
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = main.cpp complex.cpp
OBJ = $(SRC:.cpp=.o)
HEADERS = tree.hpp complex.hpp
DEPS = $(HEADERS)
EXEC = tree
TEST_EXEC = test

all: $(EXEC) $(TEST_EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

$(TEST_EXEC): test.o $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LIBS)

valgrind: $(EXEC)
	valgrind --leak-check=full ./$(EXEC)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(EXEC) $(OBJ) $(TEST_EXEC) *.o

.PHONY: all clean
