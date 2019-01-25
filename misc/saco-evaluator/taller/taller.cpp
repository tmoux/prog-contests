#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int N, M;
vector<int> dirs[maxn];

bool search(int i, int f) {
    if (i == f) return true;
    for (int j: dirs[i]) {
        if (search(j,f)) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        dirs[a].push_back(b);
    }
    int p, q; cin >> p >> q;
    if (search(p,q)) {
        cout << "yes\n";
    }
    else if (search(q,p)) {
        cout << "no\n";
    }
    else cout << "unknown\n";

    return 0;
}

