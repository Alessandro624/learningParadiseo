#include <iostream>
using namespace std;

#include "eo"

#include "utils/eoRealVectorBounds.h"

// definition of representation
#include "eoOneMax.h"
#include "eoSerializableOneMax.h"

// GENOTYPE
// definition of EO objects using fitness type (double for maximization, eoMinimizingFitness for minimization)
typedef eoSerializableOneMax<double> IndiMax;
typedef eoSerializableOneMax<eoMinimizingFitness> IndiMin;

// create an initializer: this is NOT representation-independent
// and will be done in the main file
// However, should you decide to freeze that part, you could use the
// following (and remove it from the main file, of course!!!)
//------------------------------------------------------------------
// #include "make_genotype_OneMax.h"
// eoInit<IndiMax> & make_genotype(eoParser& _parser, eoState&_state, IndiMax _eo)
// {
//   return do_make_genotype(_parser, _state, _eo);
// }

// eoInit<IndiMin> & make_genotype(eoParser& _parser, eoState&_state, IndiMin _eo)
// {
//   return do_make_genotype(_parser, _state, _eo);
// }

// same thing for the variation operaotrs
//---------------------------------------
// #include "make_op_OneMax.h"
// eoGenOp<IndiMax>&  make_op(eoParser& _parser, eoState& _state, eoInit<IndiMax>& _init)
// {
//   return do_make_op(_parser, _state, _init);
// }

// eoGenOp<IndiMin>&  make_op(eoParser& _parser, eoState& _state, eoInit<IndiMin>& _init)
// {
//   return do_make_op(_parser, _state, _init);
// }

// ***representation independent*** routines

// initialization of the population
// it IS representation independent if an eoInit is given
#include <do/make_pop.h>
eoPop<IndiMax> &make_pop(eoParser &_parser, eoState &_state, eoInit<IndiMax> &_init)
{
  return do_make_pop(_parser, _state, _init);
}

eoPop<IndiMin> &make_pop(eoParser &_parser, eoState &_state, eoInit<IndiMin> &_init)
{
  return do_make_pop(_parser, _state, _init);
}

// stopping criterion
#include <do/make_continue.h>
eoContinue<IndiMax> &make_continue(eoParser &_parser, eoState &_state, eoEvalFuncCounter<IndiMax> &_eval)
{
  return do_make_continue(_parser, _state, _eval);
}

eoContinue<IndiMin> &make_continue(eoParser &_parser, eoState &_state, eoEvalFuncCounter<IndiMin> &_eval)
{
  return do_make_continue(_parser, _state, _eval);
}

// outputs (stats, population dumps, ...)
#include <do/make_checkpoint.h>
eoCheckPoint<IndiMax> &make_checkpoint(eoParser &_parser, eoState &_state, eoEvalFuncCounter<IndiMax> &_eval, eoContinue<IndiMax> &_continue)
{
  return do_make_checkpoint(_parser, _state, _eval, _continue);
}

eoCheckPoint<IndiMin> &make_checkpoint(eoParser &_parser, eoState &_state, eoEvalFuncCounter<IndiMin> &_eval, eoContinue<IndiMin> &_continue)
{
  return do_make_checkpoint(_parser, _state, _eval, _continue);
}

// evolution engine (selection and replacement)
#include <do/make_algo_scalar.h>
eoAlgo<IndiMax> &make_algo_scalar(eoParser &_parser, eoState &_state, eoEvalFunc<IndiMax> &_eval, eoContinue<IndiMax> &_continue, eoGenOp<IndiMax> &_op)
{
  return do_make_algo_scalar(_parser, _state, _eval, _continue, _op);
}

eoAlgo<IndiMin> &make_algo_scalar(eoParser &_parser, eoState &_state, eoEvalFunc<IndiMin> &_eval, eoContinue<IndiMin> &_continue, eoGenOp<IndiMin> &_op)
{
  return do_make_algo_scalar(_parser, _state, _eval, _continue, _op);
}

// simple call to the algo
#include <do/make_run.h>
void run_ea(eoAlgo<IndiMax> &_ga, eoPop<IndiMax> &_pop)
{
  do_run(_ga, _pop);
}

void run_ea(eoAlgo<IndiMin> &_ga, eoPop<IndiMin> &_pop)
{
  do_run(_ga, _pop);
}
