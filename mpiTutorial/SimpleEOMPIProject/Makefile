CXX = mpicxx
PARADISEO = ../../lib/paradiseo-3.0.0
MPI = $(PARADISEO)/eo/src/mpi
COMMON_HEADERS = eoOneMax.h \
                 eoSerializableOneMax.h \
                 eoReuseSamePopOneMaxEA.h \
                 eoOneMaxEvalFunc.h \
                 eoOneMaxInit.h \
                 eoOneMaxMutation.h \
                 eoOneMaxOnePointQuadCrossover.h \
                 eoOneMaxTwoPointQuadCrossover.h \
                 eoOneMaxUniformQuadCrossover.h \
                 make_genotype_OneMax.h \
                 make_op_OneMax.h
CXXFLAGS = -DHAVE_GNUPLOT -DWITH_MPI -I $(PARADISEO)/eo/src -I $(MPI) -I . -Wno-deprecated-declarations -Wall -Wextra -MMD -MP
LDFLAGS = -DHAVE_GNUPLOT -DWITH_MPI -L$(PARADISEO)/build/lib/ -leompi -leoserial -lmoeo -les -lga -leo -leoutils -lcma -lm

SRC_LIB = OneMaxMpiEA.cpp make_OneMax.cpp
OBJ_LIB = $(SRC_LIB:.cpp=.o)

ALL = OneMaxMpiEA

default: clean all

all: $(ALL)

OneMaxMpiEA: $(OBJ_LIB)
	$(CXX) $(OBJ_LIB) -o $@ $(LDFLAGS)

%.o: %.cpp $(COMMON_HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_NO_LIB) $(OBJ_LIB) $(ALL) *.d *.sav *.xg *.status *~
