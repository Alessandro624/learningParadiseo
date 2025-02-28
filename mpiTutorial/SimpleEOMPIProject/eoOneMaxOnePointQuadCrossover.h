#ifndef eoOneMaxOnePointQuadCrossover_H
#define eoOneMaxOnePointQuadCrossover_H

#include <eoOp.h>

template <class GenotypeT>
class eoOneMaxOnePointQuadCrossover : public eoQuadOp<GenotypeT>
{
public:
	// add or modify the anyVariable argument
	eoOneMaxOnePointQuadCrossover()
	//  eoOneMaxOnePointQuadCrossover( varType  _anyVariable) : anyVariable(_anyVariable)
	{
	}

	/// class name used to display statistics
	string className() const { return "eoOneMaxOnePointQuadCrossover"; }

	/**
	 * eoQuad crossover - modifies both parents
	 * @param _genotype1 The first parent
	 * @param _genotype2 The second parent
	 */
	bool operator()(GenotypeT &_genotype1, GenotypeT &_genotype2)
	{
		// Creating copies
		std::vector<bool> chrom1 = _genotype1.B();
		std::vector<bool> chrom2 = _genotype2.B();
		// crossover is not possible if the genotypes are too small
		if (chrom1.size() < 2)
			return false;
		// crossover point between 1 and size-1
		unsigned crossoverPoint = rng.random(chrom1.size() - 1) + 1;
		// one point bit swap
		for (unsigned i = crossoverPoint; i < chrom1.size(); ++i)
			std::swap(chrom1[i], chrom2[i]);
		// setting the modified copies
		_genotype1.setB(chrom1);
		_genotype2.setB(chrom2);
		// at least one genotype has been modified
		return true;
	}

private:
	// private data of an eoOneMaxOnePointQuadCrossover object
	// varType anyVariable;
};

#endif
