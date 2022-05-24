#include "mobius.cpp"
#include <doctest.h>

TEST_CASE("mobius function") {
  using namespace Mobius;
  mobius_sieve();
  CHECK(mu[1] == 1);
  CHECK(mu[2] == -1);
  CHECK(mu[3] == -1);
  CHECK(mu[33003] == 0);
}
