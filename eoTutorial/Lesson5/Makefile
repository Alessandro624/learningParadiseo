CXX = g++
PARADISEO = ../../lib/paradiseo-3.0.0
CXXFLAGS = -std=c++17 -DHAVE_GNUPLOT -I $(PARADISEO)/eo/src -I . -Wno-deprecated-declarations -Wall -Wextra -MMD -MP
LDFLAGS = -L$(PARADISEO)/build/lib/ -lmoeo -les -lga -leo -leoutils -lcma -lm

COMMON_HEADERS = eoOneMax.h \
                 eoOneMaxEvalFunc.h \
                 eoOneMaxInit.h \
                 eoOneMaxMutation.h \
                 eoOneMaxQuadCrossover.h \
                 make_genotype_OneMax.h \
                 make_op_OneMax.h

SRC_NO_LIB = OneMaxEA.cpp
OBJ_NO_LIB = $(SRC_NO_LIB:.cpp=.o)

SRC_LIB = OneMaxLibEA.cpp make_OneMax.cpp
OBJ_LIB = $(SRC_LIB:.cpp=.o)

ALL = OneMaxEA OneMaxLibEA

default: clean all

all: $(ALL)

OneMaxEA: $(OBJ_NO_LIB)
	$(CXX) $(OBJ_NO_LIB) -o $@ $(LDFLAGS)

OneMaxLibEA: $(OBJ_LIB)
	$(CXX) $(OBJ_LIB) -o $@ $(LDFLAGS)

%.o: %.cpp $(COMMON_HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_NO_LIB) $(OBJ_LIB) $(ALL) *.d *.sav *.xg *.status *~
