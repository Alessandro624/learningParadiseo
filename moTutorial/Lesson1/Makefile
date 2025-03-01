CXX = g++
PARADISEO = ../../lib/paradiseo-3.0.0
CXXFLAGS = -std=c++17 -I $(PARADISEO)/eo/src -I $(PARADISEO)/mo/src -I $(PARADISEO)/problems -Wno-deprecated-declarations -Wall -Wextra -MMD -MP
LDFLAGS = -L$(PARADISEO)/build/lib/ -leo -leoutils -leoserial -les -lga -lcma

SRC_SIMPLE = lesson1_simpleHC.cpp
EXEC_SIMPLE = lesson1_simpleHC
OBJ_SIMPLE = $(SRC_SIMPLE:.cpp=.o)

SRC_MAXSAT = firstImprHC_maxSAT.cpp
EXEC_MAXSAT = firstImprHC_maxSAT
OBJ_MAXSAT = $(SRC_MAXSAT:.cpp=.o)

SRC_COMB_CONT = lesson1_combinedContinuator.cpp
EXEC_COMB_CONT = lesson1_combinedContinuator
OBJ_COMB_CONT = $(SRC_COMB_CONT:.cpp=.o)

SRC_EVAL_CONT = lesson1_evalContinuator.cpp
EXEC_EVAL_CONT = lesson1_evalContinuator
OBJ_EVAL_CONT = $(SRC_EVAL_CONT:.cpp=.o)

SRC_FIRST_IMPR = lesson1_firstImprHC.cpp
EXEC_FIRST_IMPR = lesson1_firstImprHC
OBJ_FIRST_IMPR = $(SRC_FIRST_IMPR:.cpp=.o)

SRC_FIT_CONT = lesson1_fitContinuator.cpp
EXEC_FIT_CONT = lesson1_fitContinuator
OBJ_FIT_CONT = $(SRC_FIT_CONT:.cpp=.o)

SRC_FULL_EVAL = lesson1_fullEvalContinuator.cpp
EXEC_FULL_EVAL = lesson1_fullEvalContinuator
OBJ_FULL_EVAL = $(SRC_FULL_EVAL:.cpp=.o)

SRC_ITER_CONT = lesson1_iterContinuator.cpp
EXEC_ITER_CONT = lesson1_iterContinuator
OBJ_ITER_CONT = $(SRC_ITER_CONT:.cpp=.o)

SRC_NEUTRAL = lesson1_neutralHC.cpp
EXEC_NEUTRAL = lesson1_neutralHC
OBJ_NEUTRAL = $(SRC_NEUTRAL:.cpp=.o)

SRC_RANDOM_BEST = lesson1_randomBestHC.cpp
EXEC_RANDOM_BEST = lesson1_randomBestHC
OBJ_RANDOM_BEST = $(SRC_RANDOM_BEST:.cpp=.o)

EXEC = $(EXEC_SIMPLE) $(EXEC_MAXSAT) $(EXEC_COMB_CONT) $(EXEC_EVAL_CONT) $(EXEC_FIRST_IMPR) $(EXEC_FIT_CONT) $(EXEC_FULL_EVAL) $(EXEC_ITER_CONT) $(EXEC_NEUTRAL) $(EXEC_RANDOM_BEST)
OBJ = $(OBJ_SIMPLE) $(OBJ_MAXSAT) $(OBJ_COMB_CONT) $(OBJ_EVAL_CONT) $(OBJ_FIRST_IMPR) $(OBJ_FIT_CONT) $(OBJ_FULL_EVAL) $(OBJ_ITER_CONT) $(OBJ_NEUTRAL) $(OBJ_RANDOM_BEST)

default: clean all

all: $(EXEC)

$(EXEC_SIMPLE): $(OBJ_SIMPLE)
	$(CXX) $(OBJ_SIMPLE) -o $(EXEC_SIMPLE) $(LDFLAGS)

$(EXEC_MAXSAT): $(OBJ_MAXSAT)
	$(CXX) $(OBJ_MAXSAT) -o $(EXEC_MAXSAT) $(LDFLAGS)

$(EXEC_COMB_CONT): $(OBJ_COMB_CONT)
	$(CXX) $(OBJ_COMB_CONT) -o $(EXEC_COMB_CONT) $(LDFLAGS)

$(EXEC_EVAL_CONT): $(OBJ_EVAL_CONT)
	$(CXX) $(OBJ_EVAL_CONT) -o $(EXEC_EVAL_CONT) $(LDFLAGS)

$(EXEC_FIRST_IMPR): $(OBJ_FIRST_IMPR)
	$(CXX) $(OBJ_FIRST_IMPR) -o $(EXEC_FIRST_IMPR) $(LDFLAGS)

$(EXEC_FIT_CONT): $(OBJ_FIT_CONT)
	$(CXX) $(OBJ_FIT_CONT) -o $(EXEC_FIT_CONT) $(LDFLAGS)

$(EXEC_FULL_EVAL): $(OBJ_FULL_EVAL)
	$(CXX) $(OBJ_FULL_EVAL) -o $(EXEC_FULL_EVAL) $(LDFLAGS)

$(EXEC_ITER_CONT): $(OBJ_ITER_CONT)
	$(CXX) $(OBJ_ITER_CONT) -o $(EXEC_ITER_CONT) $(LDFLAGS)

$(EXEC_NEUTRAL): $(OBJ_NEUTRAL)
	$(CXX) $(OBJ_NEUTRAL) -o $(EXEC_NEUTRAL) $(LDFLAGS)

$(EXEC_RANDOM_BEST): $(OBJ_RANDOM_BEST)
	$(CXX) $(OBJ_RANDOM_BEST) -o $(EXEC_RANDOM_BEST) $(LDFLAGS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC) *.d *.sav *.xg *.status *~
