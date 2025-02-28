CXX = g++
PARADISEO = ../../lib/paradiseo-3.0.0
CXXFLAGS = -std=c++17 -I $(PARADISEO)/eo/src -Wno-deprecated-declarations
LDFLAGS = -L $(PARADISEO)/build/lib/ -leo -leoutils

SRC_BIT = FirstBitEA.cpp
EXEC_BIT = FirstBitEA
OBJ_BIT = $(SRC_BIT:.cpp=.o)

SRC_REAL = FirstRealEA.cpp
EXEC_REAL = FirstRealEA
OBJ_REAL = $(SRC_REAL:.cpp=.o)

SRC_E13 = exercise2.3.cpp
EXEC_E13 = exercise2.3
OBJ_E13 = $(SRC_E13:.cpp=.o)

default: clean all

all:$(EXEC_BIT) $(EXEC_REAL) $(EXEC_E13)

$(EXEC_BIT): $(OBJ_BIT)
	$(CXX) $(OBJ_BIT) -o $(EXEC_BIT) $(LDFLAGS)

$(EXEC_REAL): $(OBJ_REAL)
	$(CXX) $(OBJ_REAL) -o $(EXEC_REAL) $(LDFLAGS)

$(EXEC_E13): $(OBJ_E13)
	$(CXX) $(OBJ_E13) -o $(EXEC_E13) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY clean:
	rm -f $(OBJ_BIT) $(EXEC_BIT) $(OBJ_REAL) $(EXEC_REAL) $(OBJ_E13) $(EXEC_E13)
