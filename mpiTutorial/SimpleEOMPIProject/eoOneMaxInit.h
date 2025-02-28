#ifndef _eoOneMaxInit_h
#define _eoOneMaxInit_h

#include <eoInit.h>

template <class GenotypeT>
class eoOneMaxInit : public eoInit<GenotypeT>
{
public:
  // add or modify the anyVariable argument
  // eoOneMaxInit()
  eoOneMaxInit(unsigned _vecSize) : vecSize(_vecSize)
  {
  }

  /** initialize a genotype
   *
   * @param _genotype  generally a genotype that has been default-constructed
   *                   whatever it contains will be lost
   */
  void operator()(GenotypeT &_genotype)
  {
    // random initialization of an eoOneMax object
    vector<bool> b(vecSize);
    for (unsigned i = 0; i < vecSize; i++)
      b[i] = rng.flip();
    _genotype.setB(b);
    _genotype.invalidate(); // IMPORTANT in case the _genotype is old
  }

private:
  // private data of an eoOneMaxInit object
  unsigned vecSize; // size of all bitstrings that this eoInit randomize
  //  varType anyVariable;
};

#endif
