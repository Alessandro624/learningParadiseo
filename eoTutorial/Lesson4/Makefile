CXX = g++
PARADISEO = ../../lib/paradiseo-3.0.0
CXXFLAGS = -std=c++17 -DHAVE_GNUPLOT -I $(PARADISEO)/eo/src -Wno-deprecated-declarations -Wall -Wextra -MMD -MP
LDFLAGS = -L$(PARADISEO)/build/lib/ -lmoeo -les -lga -leo -leoutils -ledoutils -lcma

SRC_BIT = BitEA.cpp
EXEC_BIT = BitEA
OBJ_BIT = $(SRC_BIT:.cpp=.o)

SRC_REAL = RealEA.cpp
EXEC_REAL = RealEA
OBJ_REAL = $(SRC_REAL:.cpp=.o)

SRC_ES = ESEA.cpp
EXEC_ES = ESEA
OBJ_ES = $(SRC_ES:.cpp=.o)

ALL_EXEC = $(EXEC_BIT) $(EXEC_REAL) $(EXEC_ES)
ALL_OBJ = $(OBJ_BIT) $(OBJ_REAL) $(OBJ_ES)

default: all

all: $(ALL_EXEC)

$(EXEC_BIT): $(OBJ_BIT)
	$(CXX) $(OBJ_BIT) -o $(EXEC_BIT) $(LDFLAGS)

$(EXEC_REAL): $(OBJ_REAL)
	$(CXX) $(OBJ_REAL) -o $(EXEC_REAL) $(LDFLAGS)

$(EXEC_ES): $(OBJ_ES)
	$(CXX) $(OBJ_ES) -o $(EXEC_ES) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(ALL_OBJ:.o=.d)

.PHONY: clean
clean:
	$(RM) $(ALL_OBJ) $(ALL_EXEC) *.d
	$(RM) *.sav *.xg *.status *~
