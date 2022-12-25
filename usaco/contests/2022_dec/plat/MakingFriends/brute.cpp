#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int N, M;

bool adj[maxn][maxn];
bool friends[maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  for (int i = 0; i < M; i++) {
    int a, b; cin >> a >> b;
    adj[a][b] = adj[b][a] = true;
    friends[a][b] = friends[b][a] = true;
  }

  int ans = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = i+1; j <= N; j++) {
      if (!adj[i][j]) {
        bool p = false;
        for (int k = 1; k < i; k++) {
          if (friends[k][i] && friends[k][j]) {
            p = true;
            break;
          }
        }

        if (p) {
          friends[i][j] = true;
          ans++;
        }
      }
    }
  }

  cout << ans << '\n';
}
