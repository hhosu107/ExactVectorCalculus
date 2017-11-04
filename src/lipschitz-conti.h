#ifndef LIPSCHITZ_CONTI_H
#define LIPSCHITZ_CONTI_H
#endif

#include "iRRAM.h"
#include "iRRAM/core.h"
#include "iRRAM/FUNCTION.h"

#include<vector>
#include<stack>
#include<functional>
#include<memory>

using namespace iRRAM;

/*
template<class RESULT,class... PARAM>
class Lipschitz {
  public:
    virtual ~Lipschitz() = 0;
    virtual FUNCTION<RESULT, PARAM...> fp = 0; // inspired from FUNCTION.h
    virtual unsigned int dimension = 0; // Domain is a subset of R^d
    virtual std::vector<unsigned int> deriv = 0; // k = (k_1, \dots, k_d) continuously differentiable
    virtual unsigned int lip = 0; // fp^(k) is lip-lipschitz conti
    // virtual REAL apply(std::vector<REAL> x) = 0; currently FUNCTION does evaluation.
};
*/
template<class RESULT,class... PARAM>
class Lipschitz {
  public:
    virtual ~Lipschitz() = 0;
    FUNCTION<RESULT, PARAM...> _fp; // inspired from FUNCTION.h
    unsigned int _dim; // Domain is a subset of R^d
    std::vector<unsigned int> _deriv; // k = (k_1, \dots, k_d) continuously differentiable
    unsigned int _lip; // fp^(k) is lip-lipschitz conti
    // virtual REAL apply(std::vector<REAL> x) = 0; currently FUNCTION does evaluation.
    Lipschitz(const FUNCTION<RESULT, PARAM...> &fp, const unsigned int &dim, const std::vector<unsigned int> &deriv, const unsigned int &lip) {
      _fp = fp;
      _dim = dim;
      _deriv = deriv;
      _lip = lip;
    }
};
