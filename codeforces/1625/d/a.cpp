#include <iostream>
#include <vector>


int main() {
  std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
  std::vector<int> a;
  std::vector<int> b = {1, 2, 3};
  a.insert(a.end(), b.begin(), b.end());

  for (int x: a) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}
