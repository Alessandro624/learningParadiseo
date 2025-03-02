#include <iostream>
#include <ctime> // sequential timing
#include <mpi.h> // parallel timing
using namespace std;

#include <eo>
#include <mpi/eoMultiStart.h>
#include <mpi/eoParallelApply.h>
#include <eoPopEvalFunc.h>
using namespace eo::mpi;

#include "utils/eoRealVectorBounds.h"
#include "eoReuseSamePopOneMaxEA.h"

// definition of representation
#include "eoOneMax.h"
#include "eoSerializableOneMax.h"

// definition of initilization
#include "eoOneMaxInit.h"

// definition of evaluation
#include "eoOneMaxEvalFunc.h"

// GENOTYPE
// definition of EO objects using fitness type (double for maximization, eoMinimizingFitness for minimization)
typedef eoSerializableOneMax<double> Indi;

// parallel eval wrapper
class ParallelEvalWrapper : public eoEvalFunc<Indi>
{
public:
  ParallelEvalWrapper(eoParallelPopLoopEval<Indi> &popEval) : _popEval(popEval) {}

  void operator()(Indi &indi) override
  {
    eoPop<Indi> singlePop;
    singlePop.push_back(indi);
    _popEval(singlePop, singlePop);
    indi.fitness(singlePop[0].fitness());
  }

private:
  eoParallelPopLoopEval<Indi> &_popEval;
};

// creation of initializer
#include "make_genotype_OneMax.h"
eoInit<Indi> &make_genotype(eoParser &_parser, eoState &_state, Indi _eo)
{
  return do_make_genotype(_parser, _state, _eo);
}

// creation of variation operaotrs
#include "make_op_OneMax.h"
eoGenOp<Indi> &make_op(eoParser &_parser, eoState &_state, eoInit<Indi> &_init)
{
  return do_make_op(_parser, _state, _init);
}

// The representation independent routines declared here

// initialization of the population
// it IS representation independent if an eoInit is given
eoPop<Indi> &make_pop(eoParser &_parser, eoState &_state, eoInit<Indi> &_init);

// stopping criterion
eoContinue<Indi> &make_continue(eoParser &_parser, eoState &_state, eoEvalFuncCounter<Indi> &_eval);

// outputs (stats, population dumps, ...)
eoCheckPoint<Indi> &make_checkpoint(eoParser &_parser, eoState &_state, eoEvalFuncCounter<Indi> &_eval, eoContinue<Indi> &_continue);

// evolution engine (selection and replacement)
eoAlgo<Indi> &make_algo_scalar(eoParser &_parser, eoState &_state, eoEvalFunc<Indi> &_eval, eoContinue<Indi> &_continue, eoGenOp<Indi> &_op);

// simple call to the algo
void run_ea(eoAlgo<Indi> &_ga, eoPop<Indi> &_pop);

int main(int argc, char *argv[])
{
  double start_time = 0.0, end_time = 0.0;
  try
  {
    Node::init(argc, argv);
    // prosess rank
    int rank = Node::comm().rank();
    // for user-parameter reading
    eoParser parser(argc, argv);
    // keeps all things allocated
    eoState state;
    // type of parallelization
    eoValueParam<string> parallelParam("multistart", "parallelType", "Type of parallelization (multistart, eval, seq)");
    parser.processParam(parallelParam, "Parallelization");
    // the fitness
    eoOneMaxEvalFunc<Indi> plainEval;
    // evaluation counter
    eoEvalFuncCounter<Indi> eval(plainEval);
    // the genotype
    eoInit<Indi> &init = make_genotype(parser, state, Indi());
    // variation operator
    eoGenOp<Indi> &op = make_op(parser, state, init);
    // initialize the population
    eoPop<Indi> &pop = make_pop(parser, state, init);
    // stopping criteria
    eoContinue<Indi> &term = make_continue(parser, state, eval);
    // output
    eoCheckPoint<Indi> &checkpoint = make_checkpoint(parser, state, eval, term);
    // algorithm
    eoAlgo<Indi> &ga = make_algo_scalar(parser, state, eval, checkpoint, op);
    // help and status
    make_parallel(parser);
    make_help(parser);
    // parallel algorithm configuration
    DynamicAssignmentAlgorithm assignmentAlgo;
    // parallelization type
    string parallelType = parallelParam.value();
    std::transform(parallelType.begin(), parallelType.end(), parallelType.begin(), ::tolower);
    if (parallelType == "multistart")
    {
      // multistart configuration for multiple parallel execution with different seeds
      eoReuseSamePopOneMaxEA<Indi> resetAlgo(term, pop, eval);
      GetRandomSeeds<Indi> getSeeds(time(0));
      // store configuration
      MultiStartStore<Indi> store(ga, DEFAULT_MASTER, resetAlgo, getSeeds);
      // job configuration with 10 parallel executions
      MultiStart<Indi> msjob(assignmentAlgo, DEFAULT_MASTER, store, 10);
      if (msjob.isMaster())
        start_time = MPI_Wtime();
      msjob.run();
      // final output
      if (msjob.isMaster())
      {
        end_time = MPI_Wtime();
        cout << "Tempo di esecuzione MPI: " << end_time - start_time << " secondi" << endl;
        cout << "Migliori individui trovati: " << endl;
        msjob.best_individuals().sortedPrintOn(cout);
        cout << endl;
        cout << "Miglior individuo trovato ha fitness: "
             << msjob.best_individuals().best_element().fitness() << endl;
      }
    }
    else if (parallelType == "eval")
    {
      if (rank == DEFAULT_MASTER)
      {
        // MASTER NODE
        // store of parallel evaluation
        ParallelApplyStore<Indi> store(eval, DEFAULT_MASTER);
        // evaluation wrapping
        store.wrapHandleResponse(new HandleResponseParallelApply<Indi>);
        // parallel evaluation
        eoParallelPopLoopEval<Indi> popEval(assignmentAlgo, DEFAULT_MASTER, &store);
        // wrapper for parallel evaluation
        ParallelEvalWrapper parallelEval(popEval);
        // parallel algorithm
        eoAlgo<Indi> &pga = make_algo_scalar(parser, state, parallelEval, checkpoint, op);
        if (rank == 0)
          start_time = MPI_Wtime();
        // evaluation of the initial population
        popEval(pop, pop);
        // print the initial population
        cout << "Initial Population\n";
        pop.sortedPrintOn(cout);
        cout << endl;
        // run the algorithm
        run_ea(pga, pop);
        if (rank == 0)
        {
          end_time = MPI_Wtime();
          cout << "Tempo di esecuzione MPI: " << end_time - start_time << " secondi" << endl;
        }
        // print the final population
        cout << "Final Population\n";
        pop.sortedPrintOn(cout);
        cout << endl;
      }
      else
      {
        // WORKER NODE
        // parallel evaluation
        eoParallelPopLoopEval<Indi> popEval(assignmentAlgo, DEFAULT_MASTER, eval);
        popEval(pop, pop);
      }
    }
    else if (parallelType == "seq")
    {
      if (rank == DEFAULT_MASTER)
      {
        clock_t seq_start = clock();
        // sequential execution
        apply<Indi>(eval, pop);
        // initial population
        cout << "Initial Population\n";
        pop.sortedPrintOn(cout);
        cout << endl;
        // run the algorithm
        run_ea(ga, pop);
        clock_t seq_end = clock();
        // final population
        cout << "Final Population\n";
        pop.sortedPrintOn(cout);
        cout << endl;
        cout << "Tempo di esecuzione sequenziale: "
             << double(seq_end - seq_start) / CLOCKS_PER_SEC << " secondi" << endl;
      }
    }
    else
    {
      throw runtime_error("Unknown parallelization type");
    }
  }
  catch (exception &e)
  {
    cout << e.what() << endl;
  }
  return 0;
}
