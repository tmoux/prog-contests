#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 20201227;
int subject_num = 7;
int step(int x) {
  return (1LL*x*subject_num) % M;
}

int iterate(int sub, int loop) {
  int x = 1;
  for (int i = 0; i < loop; i++) {
    x = (1LL*x*sub) % M;
  }
  return x;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int cardPub = 6270530;
  int doorPub = 14540258;
  //int cardPub = 5764801;
  //int doorPub = 17807724;

  int x = 1;
  int cardLoop = -1, doorLoop = -1;
  for (int i = 1; i <= M+5; i++) {
    x = step(x);
    //cout << i << ": " << x << '\n';
    if (x == cardPub) {
      cout << "card " << i << '\n';
      if (cardLoop == -1) cardLoop = i;
    }
    else if (x == doorPub) {
      cout << "door " << i << '\n';
      if (doorLoop == -1) doorLoop = i;
    }
  }
  cout << iterate(cardPub,doorLoop) << '\n';
  cout << iterate(doorPub,cardLoop) << '\n';
}

