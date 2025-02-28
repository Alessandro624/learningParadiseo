#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// standard includes
#include <fstream>
#include <iostream>  // cout
#include <stdexcept> // runtime_error

// the general include for eo
#include <eo>

// EVAL
#include "binary_value.h"

#include <ga.h> // bitstring representation & operators
// define genotype and fitness types
typedef eoBit<eoMinimizingFitness> Indi;

using namespace std;

void main_function(int argc, char **argv)
{
  // parser from the command-line arguments
  eoParser parser(argc, argv);
  eoValueParam<uint32_t> seedParam(time(0), "seed", "Random number seed", 'S');
  parser.processParam(seedParam);
  unsigned seed = seedParam.value();
  // description of genotype
  eoValueParam<unsigned int> vecSizeParam(100, "vecSize", "Genotype size", 'V');
  parser.processParam(vecSizeParam, "Representation");
  unsigned vecSize = vecSizeParam.value();
  // parameters for evolution engine
  eoValueParam<unsigned int> popSizeParam(100, "popSize", "Population size", 'P');
  parser.processParam(popSizeParam, "Evolution engine");
  unsigned popSize = popSizeParam.value();
  eoValueParam<unsigned int> tSizeParam(10, "tSize", "Tournament size", 'T');
  parser.processParam(tSizeParam, "Evolution Engine");
  unsigned tSize = tSizeParam.value();
  // init and stop
  eoValueParam<string> loadNameParam("", "Load", "A save file to restart from", 'L');
  parser.processParam(loadNameParam, "Persistence");
  string loadName = loadNameParam.value();
  eoValueParam<unsigned int> maxGenParam(500, "maxGen", "Maximum number of generations", 'G');
  parser.processParam(maxGenParam, "Stopping criterion");
  unsigned maxGen = maxGenParam.value();
  eoValueParam<unsigned int> minGenParam(500, "minGen", "Minimum number of generations", 'g');
  parser.processParam(minGenParam, "Stopping criterion");
  unsigned minGen = minGenParam.value();
  eoValueParam<unsigned int> steadyGenParam(100, "steadyGen", "Number of generations with no improvement", 's');
  parser.processParam(steadyGenParam, "Stopping criterion");
  unsigned steadyGen = steadyGenParam.value();
  // operators probabilities at the algorithm level
  eoValueParam<double> pCrossParam(0.6, "pCross", "Probability of Crossover", 'C');
  parser.processParam(pCrossParam, "Genetic Operators");
  double pCross = pCrossParam.value();
  eoValueParam<double> pMutParam(0.1, "pMut", "Probability of Mutation", 'M');
  parser.processParam(pMutParam, "Genetic Operators");
  double pMut = pMutParam.value();
  // relative rates for crossovers
  eoValueParam<double> onePointRateParam(1, "onePointRate", "Relative rate for one point crossover", '1');
  parser.processParam(onePointRateParam, "Genetic Operators");
  double onePointRate = onePointRateParam.value();
  eoValueParam<double> twoPointsRateParam(1, "twoPointRate", "Relative rate for two point crossover", '2');
  parser.processParam(twoPointsRateParam, "Genetic Operators");
  double twoPointsRate = twoPointsRateParam.value();
  eoValueParam<double> uRateParam(2, "uRate", "Relative rate for uniform crossover", 'U');
  parser.processParam(uRateParam, "Genetic Operators");
  double URate = uRateParam.value();
  // relative rates and private parameters for mutations;
  eoValueParam<double> pMutPerBitParam(0.01, "pMutPerBit", "Probability of flipping 1 bit in bit-flip mutation", 'b');
  parser.processParam(pMutPerBitParam, "Genetic Operators");
  double pMutPerBit = pMutPerBitParam.value();
  eoValueParam<double> bitFlipRateParam(0.01, "bitFlipRate", "Relative rate for bit-flip mutation", 'B');
  parser.processParam(bitFlipRateParam, "Genetic Operators");
  double bitFlipRate = bitFlipRateParam.value();
  eoValueParam<double> oneBitRateParam(0.01, "oneBitRate", "Relative rate for deterministic bit-flip mutation", 'D');
  parser.processParam(oneBitRateParam, "Genetic Operators");
  double oneBitRate = oneBitRateParam.value();
  // the name of the "status" file where all actual parameter values will be saved
  string str_status = parser.ProgramName() + ".status"; // default value
  eoValueParam<string> statusParam(str_status.c_str(), "status", "Status file", 'S');
  parser.processParam(statusParam, "Persistence");
  if (parser.userNeedsHelp())
  {
    parser.printHelp(cout);
    exit(1);
  }
  if (statusParam.value() != "")
  {
    ofstream os(statusParam.value().c_str());
    os << parser; // and you can use that file as parameter file
  }
  // Fitness function
  eoEvalFuncPtr<Indi, double, const vector<bool> &> plainEval(binary_value);
  eoEvalFuncCounter<Indi> eval(plainEval);
  // Initilisation of population
  // create an empty pop
  eoPop<Indi> pop;
  // create a state for reading
  eoState inState;
  inState.registerObject(rng);
  inState.registerObject(pop);
  if (loadName != "")
  {
    inState.load(loadName); // load the pop and the rng
  }
  else
  {
    rng.reseed(seed);
    // a Indi random initializer
    eoUniformGenerator<bool> uGen;
    eoInitFixedLength<Indi> random(vecSize, uGen);
    // Init pop from the randomizer
    pop.append(popSize, random);
    // evaluate pop
    apply<Indi>(eval, pop);
  }
  // Print intial population (raw printout)
  cout << "Initial Population" << endl
       << pop;
  cout << "and best is " << pop.best_element() << "\n\n";
  cout << "and worse is " << pop.worse_element() << "\n\n";
  // robust tournament selection
  eoDetTournamentSelect<Indi> selectOne(tSize); // tSize in [2,POPSIZE]
  // encapsulated in a eoSelectPerc (entage)
  eoSelectPerc<Indi> select(selectOne); // by default rate==1
  // REPLACE
  eoGenerationalReplacement<Indi> replace;
  // encapsulate it in the elitist replacement
  // eoWeakElitistReplacement<Indi> replace(replace_main);
  // 1-point crossover for bitstring
  eo1PtBitXover<Indi> xover1;
  // uniform crossover for bitstring
  eoUBitXover<Indi> xoverU;
  // 2-pots xover
  eoNPtsBitXover<Indi> xover2(2);
  // Combine them with relative rates
  eoPropCombinedQuadOp<Indi> xover(xover1, onePointRate);
  xover.add(xoverU, URate);
  xover.add(xover2, twoPointsRate);
  // standard bit-flip mutation for bitstring
  eoBitMutation<Indi> mutationBitFlip(pMutPerBit);
  // mutate exactly 1 bit per individual
  eoDetBitFlip<Indi> mutationOneBit;
  // Combine them with relative rates
  eoPropCombinedMonOp<Indi> mutation(mutationBitFlip, bitFlipRate);
  mutation.add(mutationOneBit, oneBitRate, true);
  // encapsulated into an eoTRansform object
  eoSGATransform<Indi> transform(xover, pCross, mutation, pMut);
  eoGenContinue<Indi> genCont(maxGen);
  eoSteadyFitContinue<Indi> steadyCont(minGen, steadyGen);
  // eoFitContinue<Indi> fitCont(vecSize);   // remove if minimizing
  eoCombinedContinue<Indi> continuator(genCont);
  continuator.add(steadyCont);
  // continuator.add(fitCont);
#ifndef _MSC_VER
  eoCtrlCContinue<Indi> ctrlC;
  continuator.add(ctrlC);
#endif
  eoCheckPoint<Indi> checkpoint(continuator);
  // counter parameter
  eoValueParam<unsigned> generationCounter(0, "Gen.");
  eoIncrementor<unsigned> increment(generationCounter.value());
  checkpoint.add(increment);
  // Best fitness in population
  eoBestFitnessStat<Indi> bestStat;
  eoAverageStat<Indi> averageStat;
  // Second moment stats: average and stdev
  eoSecondMomentStats<Indi> SecondStat;
  // the Fitness Distance Correlation
  eoQuadDistance<Indi> dist; // Hamming distance
  eoFDCStat<Indi> fdcStat(dist);
  checkpoint.add(bestStat);
  checkpoint.add(averageStat);
  checkpoint.add(SecondStat);
  checkpoint.add(fdcStat);
  eoStdoutMonitor monitor;
  checkpoint.add(monitor);
  monitor.add(generationCounter);
  monitor.add(eval);
  monitor.add(bestStat);
  monitor.add(SecondStat);
  monitor.add(fdcStat);
  // file monitor
  eoFileMonitor fileMonitor("stats.xg", " ");
  checkpoint.add(fileMonitor);
  fileMonitor.add(generationCounter);
  fileMonitor.add(bestStat);
  fileMonitor.add(SecondStat);
#ifndef _MSC_VER
  // eoGnuplot1DMonitor will 1-print to a file, and 2- plot on screen
  eoGnuplot1DMonitor gnuMonitor("best_average.xg", minimizing_fitness<Indi>());
  checkpoint.add(gnuMonitor);
  gnuMonitor.add(eval);
  gnuMonitor.add(bestStat);
  gnuMonitor.add(averageStat);
  // send a scaling command to gnuplot
  gnuMonitor.gnuplotCommand("set yrange [0:500]");
  // a specific plot monitor for FDC
  eoFDCFileSnapshot<Indi> fdcFileSnapshot(fdcStat);
  eoGnuplot1DSnapshot fdcGnuplot(fdcFileSnapshot);
  checkpoint.add(fdcFileSnapshot);
  checkpoint.add(fdcGnuplot);
  eoScalarFitnessStat<Indi> fitStat;
  checkpoint.add(fitStat);
  eoGnuplot1DSnapshot fitSnapshot("Fitnesses");
  fitSnapshot.add(fitStat);
  checkpoint.add(fitSnapshot);
#endif
  eoState outState;
  outState.registerObject(rng);
  outState.registerObject(pop);
  eoCountedStateSaver stateSaver1(100, outState, "generation");
  // save state every 1 seconds
  eoTimedStateSaver stateSaver2(1, outState, "time");
  checkpoint.add(stateSaver1);
  checkpoint.add(stateSaver2);
  // the algorithm
  eoEasyEA<Indi> gga(checkpoint, eval, select, transform, replace);
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
