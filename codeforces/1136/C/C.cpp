#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int n, m;
int a[maxn][maxn], b[maxn][maxn];
map<int,int> ca[2*maxn], cb[2*maxn];

bool mapequal(map<int,int>& a, map<int,int>& b) {
    for (auto p: a) {
        if (b[p.first] != p.second) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            ca[i+j][a[i][j]]++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> b[i][j];
            cb[i+j][b[i][j]]++;
        }
    }

    for (int i = 0; i <= n+m; i++) {
        if (!mapequal(ca[i],cb[i]) || !mapequal(cb[i],ca[i])) {
            cout << "NO" << '\n';
            return 0;
        }
    }
    cout << "YES" << '\n';
}

