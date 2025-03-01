CXX = g++
PARADISEO = ../../lib/paradiseo-3.0.0
CXXFLAGS = -std=c++17 -I $(PARADISEO)/eo/src -I $(PARADISEO)/mo/src -I $(PARADISEO)/problems -Wno-deprecated-declarations -Wall -Wextra -MMD -MP
LDFLAGS = -L$(PARADISEO)/build/lib/ -leo -leoutils -leoserial -les -lga -lcma

SRC = testSimpleTS.cpp
EXEC = testSimpleTS
OBJ = $(SRC:.cpp=.o)

default: clean all

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC) *.d *.sav *.xg *.status *~ *.out
