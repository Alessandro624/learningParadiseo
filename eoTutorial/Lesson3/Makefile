CXX = g++
PARADISEO = ../../lib/paradiseo-3.0.0
CXXFLAGS = -std=c++17 -DHAVE_GNUPLOT -I $(PARADISEO)/eo/src -Wno-deprecated-declarations
LDFLAGS = -L $(PARADISEO)/build/lib/ -leo -leoutils

SRC_BIT = SecondBitEA.cpp
EXEC_BIT = SecondBitEA
OBJ_BIT = $(SRC_BIT:.cpp=.o)
STATS_BIT = $(EXEC_BIT).status

SRC_REAL = SecondRealEA.cpp
EXEC_REAL = SecondRealEA
OBJ_REAL = $(SRC_REAL:.cpp=.o)
STATS_REAL = $(EXEC_REAL).status

SRC_E13 = exercise3.1.cpp
EXEC_E13 = exercise3.1
OBJ_E13 = $(SRC_E13:.cpp=.o)
STATS_E13 = $(EXEC_E13).status

FITDIR = Fitnesses
FDCDIR = tmpFDC
BESTAVGFILE = best_average.xg
GENFILES = generation*.sav
STATSFILE = stats.xg
TIMEFILES = time*.sav

default: all

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
	rm -f $(OBJ_BIT) $(EXEC_BIT) $(STATS_BIT) $(OBJ_REAL) $(EXEC_REAL) $(STATS_REAL) $(OBJ_E13) $(EXEC_E13) $(STATS_E13)
	rm -f $(FITDIR)/* $(FDCDIR)/* $(BESTAVGFILE) $(GENFILES) $(STATSFILE) $(TIMEFILES)
	rm -fd $(FITDIR) $(FDCDIR)
