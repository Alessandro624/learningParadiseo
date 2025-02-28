#ifndef _make_genotype_h
#define _make_genotype_h

#include <eoOneMax.h>
#include <eoOneMaxInit.h>

// parser and param includes
#include <utils/eoParser.h>
#include <utils/eoState.h>

template <class EOT>
eoInit<EOT> &do_make_genotype(eoParameterLoader &_parser, eoState &_state, EOT)
{
  // read any useful parameter here from the parser
  // paramType & param = _parser.createParam(deafultValue, "Keyword", "Comment to appear in help and status", 'c',"Section of status file").value();
  unsigned vecSize = _parser.createParam(unsigned(8), "VecSize", "Size of the bitstrings", 'v', "Representation").value();
  // the initializer - a pointer, stored in the eoState
  eoInit<EOT> *init = new eoOneMaxInit<EOT>(vecSize);
  // store in state
  _state.storeFunctor(init);
  return *init;
}

#endif
