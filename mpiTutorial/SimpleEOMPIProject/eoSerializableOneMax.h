#ifndef _eoSerializableOneMax_h
#define _eoSerializableOneMax_h

#include <es.h>
#include <eoOneMax.h>
#include <eo>
#include <serial/eoSerial.h>

template <class FitT>
class eoSerializableOneMax : public eoOneMax<FitT>, public eoserial::Persistent
{
public:
    eoSerializableOneMax(unsigned size = 0) : eoOneMax<FitT>()
    {
        std::vector<bool> bits(size, false);
        this->setB(bits);
    }

    eoserial::Object *pack() const override
    {
        eoserial::Object *obj = new eoserial::Object;
        obj->add("bits", eoserial::makeArray<std::vector<bool>, eoserial::MakeAlgorithm>(this->B()));
        bool invalidFitness = this->invalid();
        obj->add("invalid", eoserial::make(invalidFitness));
        if (!invalidFitness)
        {
            obj->add("fitness", eoserial::make(this->fitness()));
        }
        return obj;
    }

    void unpack(const eoserial::Object *obj) override
    {
        this->clear();
        std::vector<bool> B;
        eoserial::unpackArray<std::vector<bool>, eoserial::Array::UnpackAlgorithm>(*obj, "bits", B);
        this->setB(B);
        bool invalidFitness;
        eoserial::unpack(*obj, "invalid", invalidFitness);
        if (invalidFitness)
        {
            this->invalidate();
        }
        else
        {
            FitT fitnessVal;
            eoserial::unpack(*obj, "fitness", fitnessVal);
            this->fitness(fitnessVal);
        }
    }
};

#endif
