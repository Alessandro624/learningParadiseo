#ifndef eoOneMaxTwoPointQuadCrossover_H
#define eoOneMaxTwoPointQuadCrossover_H

#include <eoOp.h>

template <class GenotypeT>
class eoOneMaxTwoPointQuadCrossover : public eoQuadOp<GenotypeT>
{
public:
    // add or modify the anyVariable argument
    eoOneMaxTwoPointQuadCrossover()
    //  eoOneMaxTwoPointQuadCrossover( varType  _anyVariable) : anyVariable(_anyVariable)
    {
    }

    /// class name used to display statistics
    string className() const { return "eoOneMaxTwoPointQuadCrossover"; }

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
        if (chrom1.size() < 3)
            return false;
        // two crossover points between 1 and size-1 with point1 < point2
        unsigned point1 = rng.random(chrom1.size() - 1);
        unsigned point2 = rng.random(chrom1.size() - point1 - 1) + point1 + 1;
        // two point bit swap
        for (unsigned i = point1; i < point2; ++i)
            std::swap(chrom1[i], chrom2[i]);
        // setting the modified copies
        _genotype1.setB(chrom1);
        _genotype2.setB(chrom2);
        // at least one genotype has been modified
        return true;
    }

private:
    // private data of an eoOneMaxTwoPointQuadCrossover object
    // varType anyVariable;
};

#endif
