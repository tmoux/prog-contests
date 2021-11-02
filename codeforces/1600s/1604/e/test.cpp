#include <bits/stdc++.h>

int main() {
  auto almost_gcd = [](auto gcd, int a, int b) -> int {
    return b == 0 ? a : gcd(b, a % b);
  };
  auto gcd = std::y_combinator(std::ref(almost_gcd));
}
