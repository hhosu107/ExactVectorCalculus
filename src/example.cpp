#include "lipschitz-conti.h"

#include "iRRAM.h"
#include "iRRAM/core.h"
// #include "iRRAM/FUNCTION.h"
#include <iostream>
#include <vector>

using namespace iRRAM;

REAL sin_TAYLOR( int accuracy, REAL x /*const REAL& x, const unsigned int& accuracy */){
  // Accuracy filter: \geq 1.
  // Note that after i-times approximation, difference between real value and approximated value is not bigger than 1/(2i-1)! + 1/(2i+1)! + 1/(2i+3)! + ... \leq 1/(2i-2)! \leq 2^(2i-2).
  // To compute derivative of sin with error bound 2^(-i), it requires 2^-(2i+3) error bound, so when our desired error bound is 2^(-i), let's put i+3 for the accuracy. Assume accuracy \geq 1.
  REAL y=x;
  REAL res=(REAL)0;
  for(int i=-1; i>=accuracy; i--){
    res += y;
    y *= (REAL)(-1) * (x * x)/(REAL)((2 * i) * (2 * i - 1));
  }
  return res;
}
REAL cos_TAYLOR( int accuracy, REAL x /*const REAL& x, const unsigned int& accuracy*/){
  // Note that after i-times approximation, difference between real value and approximated value is not bigger than 1/(2i-2)! + 1/(2i)! + 1/(2i+2)! + ... \leq 1/(2i-3)! \leq 2^(2i-3).
  // To compute derivative of sin with error bound 2^(-i), it requires 2^-(2i+3) error bound, so when our desired error bound is 2^(-i), let's put i+3 for the accuracy. Assume accuracy \geq 1.
  REAL y=1;
  REAL res=(REAL)0;
  for(int i=-1; i>=accuracy; i--){
    res += y;
    y *= (int)(-1) * (x*x)/(REAL)((2 * i + 1) * (2 * i));
  }
  return (REAL)res;
}

REAL sine(REAL x){
  return limit(sin_TAYLOR, x);
}

REAL cosine(REAL x){
  return limit(cos_TAYLOR, x);
}

REAL lip_deriv(REAL (*f)(REAL), REAL x, int lip, int log_eps){
  INTEGER e = 1;
  for(int i=-1; i>=log_eps; i--){
    e *= (INTEGER)2;
  }
  REAL eps = 1 / (REAL)e;
  REAL res;
  res = (f(x+(eps/(REAL)lip)) - f(x)) * (REAL)e * (REAL)lip; // naive implementation.
  return res;
}

static void error(int i){
  cerr << i << "\n";
  exit(1);
}

void compute(){
  // Assume that we will put x \in [-1, 1].
  // The feature FUNCTION itself is hard to make it working, so make a naive code first
 
  /*
  FUNCTION<REAL, REAL, INTEGER> Sin;
  Sin = from_algorithm(sin_TAYLOR);
  FUNCTION<REAL, REAL, INTEGER> Cos;
  Cos = from_algorithm(cos_TAYLOR);
  
  Lipschitz<REAL, REAL, INTEGER> sin_lip = new Lipschitz<REAL, REAL, INTEGER>(Sin, 1, std::vector<unsigned int>(1, 1), 1);
  Lipschitz<REAL, REAL, INTEGER> cos_lip = new Lipschitz<REAL, REAL, INTEGER>(Cos, 1, std::vector<unsigned int>(1, 1), 1);
  */

  int acc;
  REAL x;
  int w;
  int retry=0;

  do{
  cout << "Print derivative of sin(x) and cos(x) with error bound 2^(-acc) and width w : Please input x, acc and w!\n";
  cin >> x;
  cin >> acc;
  cin >> w;

  REAL sin_deriv = lip_deriv(sine, x, 1, -(acc+1));
  REAL cos_deriv = lip_deriv(cosine, x, 1, -(acc+1));
  cout << "(d/dx)(sin(" ;
  cout << x << ")) = ";
  cout << setRwidth(w) << sin_deriv << ", (d/dx)(cos(";
  cout << x << ")) = ";
  cout << setRwidth(w) << cos_deriv << ".\n";
  cout << "wanna try once more? Answer 1 to retry.\n";
  cin >> retry;
  }while(retry > 0);
}
