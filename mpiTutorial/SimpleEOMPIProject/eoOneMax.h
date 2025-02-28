#ifndef _eoOneMax_h
#define _eoOneMax_h

template <class FitT>
class eoOneMax : public EO<FitT>
{
public:
  eoOneMax()
  {
  }

  virtual ~eoOneMax()
  {
  }

  virtual string className() const { return "eoOneMax"; }

  // printing ...
  void printOn(ostream &_os) const
  {
    // write the fitness
    EO<FitT>::printOn(_os);
    _os << ' ';
    // default output
    _os << b.size() << ' ';
    for (unsigned i = 0; i < b.size(); i++)
      _os << b[i] << ' ';
  }

  // reading ...
  void readFrom(istream &_is)
  {
    // read the fitness first
    EO<FitT>::readFrom(_is);
    // input
    unsigned s;
    _is >> s;
    b.resize(s);
    for (unsigned i = 0; i < s; i++)
    {
      bool bTmp;
      _is >> bTmp;
      b[i] = bTmp;
    }
  }

  // accessing and setting values
  void setB(vector<bool> &_b)
  {
    b = _b;
  }
  const vector<bool> &B() const
  {
    return b;
  }
  void clear()
  {
    b.clear();
  }

private:
  // private data of an eoOneMax object
  std::vector<bool> b;
};

#endif
