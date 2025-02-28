#ifndef _eoReuseSamePopOneMaxEA_h
#define _eoReuseSamePopOneMaxEA_h

#include <eo>
#include <mpi/eoMultiStart.h>
#include <mpi/eoMpi.h>

template <class EOT>
struct eoReuseSamePopOneMaxEA : public MultiStartStore<EOT>::ResetAlgo
{
    eoReuseSamePopOneMaxEA(
        eoContinue<EOT> &continuator,
        const eoPop<EOT> &originalPop,
        eoEvalFunc<EOT> &eval) : _continuator(continuator),
                                 _originalPop(originalPop),
                                 _firstTime(true)
    {
        for (unsigned i = 0, size = originalPop.size();
             i < size; ++i)
        {
            eval(_originalPop[i]);
        }
    }

    eoReuseSamePopOneMaxEA(
        eoContinue<EOT> &continuator,
        const eoPop<EOT> &originalPop,
        eoPopEvalFunc<EOT> &pop_eval) : _continuator(continuator),
                                        _originalPop(originalPop),
                                        _firstTime(true)
    {
        pop_eval(_originalPop, _originalPop);
    }

    void operator()(eoPop<EOT> &pop)
    {
        if (_firstTime)
        {
            pop = _originalPop;
            _firstTime = false;
        }
        // _continuator.reset();
    }

protected:
    eoContinue<EOT> &_continuator;
    eoPop<EOT> _originalPop;
    bool _firstTime;
};
#endif
