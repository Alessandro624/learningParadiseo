#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// Bitstring Genetic Algorithm
#include <iostream>
#include <stdexcept>

// the general include for eo
#include <eo>
#include <ga.h> // bitstring representation & operators
// define individuals
typedef eoBit<double> Indi; // A bitstring with fitness double

using namespace std;

// fitness function that computes the number of ones of a bitstring
double binary_value(const Indi &_indi)
{
  double sum = 0;
  for (unsigned i = 0; i < _indi.size(); i++)
    sum += _indi[i];
  return sum;
}

void main_function(int /*argc*/, char ** /*argv*/)
{
  const unsigned int SEED = 42;      // seed for random number generator
  const unsigned int VEC_SIZE = 8;   // Number of bits in genotypes
  const unsigned int POP_SIZE = 20;  // Size of population
  const unsigned int MAX_GEN = 500;  // Maximum number of generation before STOP
  const float CROSS_RATE = 0.8;      // Crossover rate
  const double P_MUT_PER_BIT = 0.01; // probability of bit-flip mutation
  const float MUT_RATE = 1.0;        // mutation rate
  //  Random seed
  rng.reseed(SEED);
  // Fitness function
  eoEvalFuncPtr<Indi> eval(binary_value);
  // Initilisation of population
  // declare the population
  eoPop<Indi> pop;
  // fill it!
  for (unsigned int igeno = 0; igeno < POP_SIZE; igeno++)
  {
    Indi v; // void individual, to be filled
    for (unsigned ivar = 0; ivar < VEC_SIZE; ivar++)
    {
      bool r = rng.flip(); // new value, random in {0,1}
      v.push_back(r);      // append that random value to v
    }
    eval(v);          // evaluate it
    pop.push_back(v); // and put it in the population
  }
  // sort pop
  pop.sort();
  // Print intial population
  cout << "Initial Population" << endl;
  cout << pop;
  // selection and replacement
  // roulette
  // eoProportionalSelect<Indi> select;
  // stochastic binary tournament selection
  // const double RATE = 0.75;
  // eoStochTournamentSelect<Indi> select(RATE);     // RATE in ]0.5,1]
  // robust tournament selection
  const unsigned int T_SIZE = 3;              // size for tournament selection
  eoDetTournamentSelect<Indi> select(T_SIZE); // T_SIZE in [2,POP_SIZE]
  // random selection
  // eoRandomSelect<Indi> select;
  // termination condition
  // stop after MAX_GEN generations
  eoGenContinue<Indi> continuator(MAX_GEN);
  // The variation operators
  // standard bit-flip mutation for bitstring
  eoBitMutation<Indi> mutation(P_MUT_PER_BIT);
  // 1-point mutation for bitstring
  eo1PtBitXover<Indi> xover;
  // the algorithm
  eoSGA<Indi> gga(select, xover, CROSS_RATE, mutation, MUT_RATE,
                  eval, continuator);
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
