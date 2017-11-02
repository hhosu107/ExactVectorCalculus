#include "lipschitz-conti.h"

#include "iRRAM/iRRAM.h"
#include "iRRAM/core.h"
#include "iRRAM/FUNCTION.h"

static REAL sin_REAL( const REAL& x, const INTEGER& accuracy){
  return (REAL)1;
}
static REAL cos_REAL( const REAL& x, const INTEGER& accuracy){
  return (REAL)1;
}

static void error(int i){
  cerr << i << "\n";
  exit(1);
}

void compute(){
}
