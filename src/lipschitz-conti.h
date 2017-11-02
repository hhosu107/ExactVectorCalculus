#ifndef LIPSCHITZ_CONTI_H
#define LIPSCHITZ_CONTI_H

#include "iRRAM/core.h"
#include "iRRAM/FUNCTION.h"

#include<vector>
#include<stack>
#include<functional>
#include<memory>

using namespace iRRAM;

class Rational {
  private:
    int p,q;

  public:
    Rational() : p(0), q(1) {}
    Rational(int p, int q) : p(p), q(q) {}

    operator REAL() const{
      return (REAL) p/q;
    }
};

template<class RESULT,class... PARAM>
class Lipschitz {
  public:
    virtual ~Lipschitz() = 0;
    virtual FUNCTION<RESULT, PARAM> fp = 0; // inspired from FUNCTION.h
    virtual unsigned int dimension = 0; // Domain is a subset of R^d
    virtual std::vector<unsigned int> deriv = 0; // k = (k_1, \dots, k_d) continuously differentiable
    virtual unsigned int lip = 0; // fp^(k) is lip-lipschitz conti
    virtual REAL apply(std::vector<REAL> x) = 0;
};
