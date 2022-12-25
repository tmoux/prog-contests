#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int M, N, Q; cin >> M >> N >> Q;
  struct D {
    char c;
    int x, y, z;
  };
  vector<D> data(N+1);
  vector<int> indegree(N+1);
  int MX = 3*N+1;
  vector<int> par(MX), nxt(MX);

  for (int i = 1; i <= N; i++) {
    char c; cin >> c;
    int x, y, z; cin >> x >> y >> z;
    data[i] = {c, x, y, z};

    if (c == 'M') {
      indegree[i] += 2;
      nxt[x] = i;
      nxt[y] = i;
      par[z] = i;
    }
    else {
      indegree[i]++;
      nxt[x] = i;
      par[y] = i;
      par[z] = i;
    }
  }

  vector<vector<int>> numPassThru(2, vector<int>(MX, 0));

  queue<array<int, 2>> q;
  numPassThru[0][1] = M;
  q.push({1, 0});

  while (!q.empty()) {
    auto [i, which] = q.front(); q.pop();
    int num = numPassThru[which][i];

    if (which == 0) {
      // output node
      int j = nxt[i];
      if (j > 0) {
        numPassThru[1][j] += num;
        if (--indegree[j] == 0) {
          q.push({j, 1});
        }
      }
    }
    else {
      // regular node
      auto [c, x, y, z] = data[i];
      if (c == 'M') {
        numPassThru[0][z] += num;
        q.push({z, 0});
      }
      else {
        numPassThru[0][y] += (num+1)/2;
        q.push({y, 0});

        numPassThru[0][z] += num/2;
        q.push({z, 0});
      }
    }
  }

  while (Q--) {
    int x, k; cin >> x >> k;
    bool poss = true;

    while (true) {
      if (k > numPassThru[0][x]) {
        poss = false;
        break;
      }

      if (x == 1) break;

      int i = par[x];
      assert(i != 0);
      auto [c, xx, yy, zz] = data[i];
      if (c == 'M') {
        assert(x == zz);
        int a = numPassThru[0][xx];
        int b = numPassThru[0][yy];

        if (k <= 2 * min(a, b)) {
          if (k % 2 == 1) {
            x = xx;
            k = (k + 1) / 2;
          }
          else {
            x = yy;
            k = k / 2;
          }
        }
        else if (k <= a + b) {
          x = a > b ? xx : yy;
          k = k - min(a, b);
        }
        else {
          // impossible
          assert(false);
        }
      }
      else {
        if (x == yy) {
          x = xx;
          k = 2*k - 1;
        }
        else {
          x = xx;
          k = 2*k;
        }
      }
    }

    if (poss) {
      cout << k << '\n';
    }
    else {
      cout << "none\n";
    }
  }
}
