// Bitstring Genetic Algorithm
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// standard includes
#include <stdexcept> // runtime_error
#include <iostream>  // cout

// the general include for eo
#include <eo>
#include <ga.h> // bitstring representation & operators
// define individuals
typedef eoBit<double> Indi; // A bitstring with fitness double

// fitness function that computes the number of ones of a bitstring
#include "binary_value.h"

using namespace std;

void main_function(int /*argc*/, char ** /*argv*/)
{
  const unsigned int SEED = 42;       // seed for random number generator
  const unsigned int T_SIZE = 3;      // size for tournament selection
  const unsigned int VEC_SIZE = 20;   // Number of bits in genotypes
  const unsigned int POP_SIZE = 20;   // Size of population
  const unsigned int MAX_GEN = 500;   // Maximum number of generation before STOP
  const unsigned int MIN_GEN = 10;    // Minimum number of generation before ...
  const unsigned int STEADY_GEN = 50; // stop after STEADY_GEN gen. without improvelent
  const double P_CROSS = 0.8;         // Crossover probability
  const double P_MUT = 1.0;           // mutation probability
  const double P_MUT_PER_BIT = 0.01;  // internal probability for bit-flip mutation
  // some parameters for chosing among different operators
  const double onePointRate = 0.5;  // rate for 1-pt Xover
  const double twoPointsRate = 0.5; // rate for 2-pt Xover
  const double URate = 0.5;         // rate for Uniform Xover
  const double bitFlipRate = 0.5;   // rate for bit-flip mutation
  const double oneBitRate = 0.5;    // rate for one-bit mutation
  //  Random seed
  rng.reseed(SEED);
  // Fitness function
  eoEvalFuncPtr<Indi, double, const vector<bool> &> eval(binary_value);
  // Initilisation of population
  eoUniformGenerator<bool> uGen;
  eoInitFixedLength<Indi> random(VEC_SIZE, uGen);
  // Initialization of the population
  eoPop<Indi> pop(POP_SIZE, random);
  // evaluate it
  apply<Indi>(eval, pop);
  // sort pop
  pop.sort();
  // Print intial population
  cout << "Initial Population" << endl;
  cout << pop;
  // robust tournament selection
  eoDetTournamentSelect<Indi> selectOne(T_SIZE); // T_SIZE in [2,POP_SIZE]
  eoSelectMany<Indi> select(selectOne, 2, eo_is_an_integer);
  // eoSelectMany<Indi> select(selectOne, 0.1);
  // eoCommaReplacement<Indi> replace;
  eoPlusReplacement<Indi> replace;
  // variation operators
  // 1-point crossover for bitstring
  eo1PtBitXover<Indi> xover1;
  // uniform crossover for bitstring
  eoUBitXover<Indi> xoverU;
  // 2-pots xover
  eoNPtsBitXover<Indi> xover2(2);
  eoPropCombinedQuadOp<Indi> xover(xover1, onePointRate);
  xover.add(xoverU, URate);
  xover.add(xover2, twoPointsRate);
  // standard bit-flip mutation for bitstring
  eoBitMutation<Indi> mutationBitFlip(P_MUT_PER_BIT);
  // mutate exactly 1 bit per individual
  eoDetBitFlip<Indi> mutationOneBit;
  eoPropCombinedMonOp<Indi> mutation(mutationBitFlip, bitFlipRate);
  mutation.add(mutationOneBit, oneBitRate, true);
  eoSGATransform<Indi> transform(xover, P_CROSS, mutation, P_MUT);
  // stop after MAX_GEN generations
  eoGenContinue<Indi> genCont(MAX_GEN);
  // do MIN_GEN gen., then stop after STEADY_GEN gen. without improvement
  eoSteadyFitContinue<Indi> steadyCont(MIN_GEN, STEADY_GEN);
  // stop when fitness reaches a target (here VEC_SIZE)
  eoFitContinue<Indi> fitCont(VEC_SIZE);
  eoCombinedContinue<Indi> continuator(genCont);
  continuator.add(steadyCont);
  continuator.add(fitCont);
  // algorithm
  eoEasyEA<Indi> gga(continuator, eval, select, transform, replace);
  // Apply algo
  gga(pop);
  // Print final population
  pop.sort();
  cout << "FINAL Population\n"
       << pop << endl;
}

int main(int argc, char **argv)
{
  try
  {
    main_function(argc, argv);
  }
  catch (exception &e)
  {
    cout << "Exception: " << e.what() << '\n';
  }

  return 1;
}
