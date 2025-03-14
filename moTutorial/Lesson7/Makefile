CXX = g++
PARADISEO = ../../lib/paradiseo-3.0.0
CXXFLAGS = -std=c++17 -I $(PARADISEO)/eo/src -I $(PARADISEO)/mo/src -I $(PARADISEO)/problems -Wno-deprecated-declarations -Wall -Wextra -MMD -MP
LDFLAGS = -L$(PARADISEO)/build/lib/ -leo -leoutils -leoserial -les -lga -lcma

SRC = hybridAlgo.cpp
EXEC = hybridAlgo
OBJ = $(SRC:.cpp=.o)

SRC_CONTINUATOR = hybridAlgoContinuator.cpp
EXEC_CONTINUATOR = hybridAlgoContinuator
OBJ_CONTINUATOR = $(SRC_CONTINUATOR:.cpp=.o)

default: clean all

all: $(EXEC) $(EXEC_CONTINUATOR)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

$(EXEC_CONTINUATOR): $(OBJ_CONTINUATOR)
	$(CXX) $(OBJ_CONTINUATOR) -o $(EXEC_CONTINUATOR) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC) $(EXEC_CONTINUATOR) $(OBJ_CONTINUATOR) *.d *.sav *.xg *.status *~ *.out
