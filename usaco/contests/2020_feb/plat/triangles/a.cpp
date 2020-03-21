#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int N;
bool grid[maxn][maxn];

int main()
{
    //freopen("triangles.in","r",stdin); freopen("triangles.out","w",stdout);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char c; cin >> c;
            grid[i][j] = c == '*';
        }
    }
}
