#ifndef eoOneMaxUniformQuadCrossover_H
#define eoOneMaxUniformQuadCrossover_H

#include <eoOp.h>

template <class GenotypeT>
class eoOneMaxUniformQuadCrossover : public eoQuadOp<GenotypeT>
{
public:
    // add or modify the anyVariable argument
    eoOneMaxUniformQuadCrossover()
    //  eoOneMaxUniformQuadCrossover( varType  _anyVariable) : anyVariable(_anyVariable)
    {
    }

    /// class name used to display statistics
    string className() const { return "eoOneMaxUniformQuadCrossover"; }

    /**
     * eoQuad crossover - modifies both parents
     * @param _genotype1 The first parent
     * @param _genotype2 The second parent
     */
    bool operator()(GenotypeT &_genotype1, GenotypeT &_genotype2)
    {
        bool modified = false;
        // Creating copies
        std::vector<bool> chrom1 = _genotype1.B();
        std::vector<bool> chrom2 = _genotype2.B();
        // uniform crossover
        for (unsigned i = 0; i < chrom1.size(); ++i)
        {
            // 50% chance of swapping bits
            if (rng.flip())
            {
                std::swap(chrom1[i], chrom2[i]);
                modified = true;
            }
        }
        // setting the modified copies
        _genotype1.setB(chrom1);
        _genotype2.setB(chrom2);
        // at least one genotype has been modified
        return modified;
    }

private:
    // private data of an eoOneMaxUniformQuadCrossover object
    // varType anyVariable;
};

#endif
