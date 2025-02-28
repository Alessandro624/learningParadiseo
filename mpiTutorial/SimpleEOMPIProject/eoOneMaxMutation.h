#ifndef eoOneMaxMutation_H
#define eoOneMaxMutation_H

#include <eoOp.h>

template <class GenotypeT>
class eoOneMaxMutation : public eoMonOp<GenotypeT>
{
public:
	// add or modify the anyVariable argument
	eoOneMaxMutation()
	// eoOneMaxMutation( varType  _anyVariable) : anyVariable(_anyVariable)
	{
	}

	/// class name used to display statistics
	string className() const { return "eoOneMaxMutation"; }

	/**
	 * modifies the parent
	 * @param _genotype The parent genotype (will be modified)
	 */
	bool operator()(GenotypeT &_genotype)
	{
		// Creating a copy
		std::vector<bool> chrom = _genotype.B();
		// select a random position
		unsigned index = rng.random(chrom.size());
		// assign a random value (0 or 1)
		chrom[index] = rng.flip();
		// setting the modified copy
		_genotype.setB(chrom);
		return true;
	}

private:
	// private data of an eoOneMaxMutation object
	//  varType anyVariable;
};

#endif
