#ifndef _eoOneMaxEvalFunc_h
#define _eoOneMaxEvalFunc_h

#include <stdexcept>
#include <fstream>

#include "eoEvalFunc.h"

template <class EOT>
class eoOneMaxEvalFunc : public eoEvalFunc<EOT>
{
public:
  // add or modify the anyVariable argument
  eoOneMaxEvalFunc()
  // eoOneMaxEvalFunc( varType  _anyVariable) : anyVariable(_anyVariable)
  {
  }

  /** Actually compute the fitness
   *
   * @param EOT & _eo the EO object to evaluate
   *                  it should stay templatized to be usable
   *                  with any fitness type
   */
  void operator()(EOT &_eo)
  {
    // test for invalid to avoid recomputing fitness of unmodified individuals
    if (_eo.invalid())
    {
      double fit; // to hold fitness value
      // computation of fitness of the eoOneMax object
      const vector<bool> &b = _eo.B();
      fit = 0;
      for (unsigned i = 0; i < b.size(); i++)
        fit += (b[i] ? 1 : 0);
      _eo.fitness(fit);
    }
  }

private:
  // private data of an eoOneMaxEvalFunc object
  // varType anyVariable;
};

#endif
