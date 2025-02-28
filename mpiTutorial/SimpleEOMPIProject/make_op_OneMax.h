#ifndef _make_op_OneMax_h
#define _make_op_OneMax_h

// the operators
#include <eoOp.h>
#include <eoGenOp.h>
#include <eoCloneOps.h>
#include <eoOpContainer.h>
// combinations of simple eoOps (eoMonOp and eoQuadOp)
#include <eoProportionalCombinedOp.h>

// definition of mutation
#include "eoOneMaxMutation.h"

// definition of crossover (either as eoBinOp (2->1) or eoQuadOp (2->2)
// #include "eoOneMaxBinOp.h"
// OR
#include "eoOneMaxOnePointQuadCrossover.h"
#include "eoOneMaxTwoPointQuadCrossover.h"
#include "eoOneMaxUniformQuadCrossover.h"

// parser and state
#include <utils/eoParser.h>
#include <utils/eoState.h>

template <class EOT>
eoGenOp<EOT> &do_make_op(eoParameterLoader &_parser, eoState &_state, eoInit<EOT> & /*_init*/)
{
  // CROSSOVER
  // first crossover
  eoQuadOp<Indi> *cross = new eoOneMaxOnePointQuadCrossover<Indi> /* (varType  _anyVariable) */;
  // store in the state
  _state.storeFunctor(cross);
  // read its relative rate in the combination
  double cross1Rate = _parser.createParam(1.0, "cross1Rate", "Relative rate for crossover 1", '1', "Variation Operators").value();
  // create the combined operator with this one
  eoPropCombinedQuadOp<Indi> *propXover = new eoPropCombinedQuadOp<Indi>(*cross, cross1Rate);
  // second crossover
  cross = new eoOneMaxTwoPointQuadCrossover<Indi> /* (varType  _anyVariable) */;
  // store in the state
  _state.storeFunctor(cross);
  // read its relative rate in the combination
  double cross2Rate = _parser.createParam(1.0, "cross2Rate", "Relative rate for crossover 2", '2', "Variation Operators").value();
  // create the combined operator with this one
  propXover->add(*cross, cross2Rate);
  // third crossover
  cross = new eoOneMaxUniformQuadCrossover<Indi> /* (varType  _anyVariable) */;
  // store in the state
  _state.storeFunctor(cross);
  // read its relative rate in the combination
  double cross3Rate = _parser.createParam(1.0, "cross3Rate", "Relative rate for crossover 3", '3', "Variation Operators").value();
  // create the combined operator with this one
  propXover->add(*cross, cross3Rate);
  // store it in the state
  _state.storeFunctor(propXover);
  /* replicate as many time as you need (second, third, ...)
      cross = new eoOneMaxSecondCrossover<Indi>(varType  _anyVariable);
      _state.storeFunctor(cross);
      double cross2Rate = _parser.createParam(1.0, "cross2Rate", "Relative rate for crossover 2", '2', "Variation Operators").value();
      propXover->add(*cross, cross2Rate);
  */
  // the last one should be like
  // propXover.add(*cross, crossXXXRate, true);

  // MUTATION
  // first mutation
  eoMonOp<Indi> *mut = new eoOneMaxMutation<Indi> /* (varType  _anyVariable) */;
  // store it in the state
  _state.storeFunctor(mut);
  // its relative rate in the combination
  double mut1Rate = _parser.createParam(1.0, "mut1Rate", "Relative rate for mutation 1", '1', "Variation Operators").value();
  // creation of the combined operator with this one
  eoPropCombinedMonOp<Indi> *propMutation = new eoPropCombinedMonOp<Indi>(*mut, mut1Rate);
  // store it in the state
  _state.storeFunctor(propMutation);
  /* replicate as many time as you need (second, third, ...)
      mut = new eoOneMaxSecondMutation<Indi>(varType  _anyVariable);
      _state.storeFunctor(mut);
      double mut2Rate = _parser.createParam(1.0, "mut2Rate", "Relative rate for mutation 2", '2', "Variation Operators").value();
       propMutation->add(*mut, mut2Rate);
  */
  // the last one should be like
  // propMutation.add(*mut, mutXXXRate, true);

  // CROSSOVER AND MUTATION
  // read the individual level parameters
  eoValueParam<double> &pCrossParam = _parser.createParam(0.6, "pCross", "Probability of Crossover", 'C', "Variation Operators");
  // minimum check
  if ((pCrossParam.value() < 0) || (pCrossParam.value() > 1))
    throw eoParamException("Invalid pCross");
  eoValueParam<double> &pMutParam = _parser.createParam(0.1, "pMut", "Probability of Mutation", 'M', "Variation Operators");
  // minimum check
  if ((pMutParam.value() < 0) || (pMutParam.value() > 1))
    throw eoParamException("Invalid pMut");
  // the crossover - with probability pCross
  eoProportionalOp<Indi> *propOp = new eoProportionalOp<Indi>;
  _state.storeFunctor(propOp);
  eoQuadOp<Indi> *ptQuad = new eoQuadCloneOp<Indi>;
  _state.storeFunctor(ptQuad);
  // crossover, with proba pcross
  propOp->add(*propXover, pCrossParam.value());
  // nothing, with proba 1-pcross
  propOp->add(*ptQuad, 1 - pCrossParam.value());
  // the sequential
  eoSequentialOp<Indi> *op = new eoSequentialOp<Indi>;
  _state.storeFunctor(op);
  // always do combined crossover
  op->add(*propOp, 1.0);
  // then mutation, with proba pmut
  op->add(*propMutation, pMutParam.value());
  return *op;
}
#endif
