#include "../utilities/template.h"

#include "../../content/number-theory/PrimeCounting.h"

int main() {
  assert(count_primes(1e10) == 455052511LL);
  assert(count_primes(1e11) == 4118054813LL);
  assert(count_primes(1e12) == 37607912018LL);
  cout << "Tests passed!" << endl;
}
