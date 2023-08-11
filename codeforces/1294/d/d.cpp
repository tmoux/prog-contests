#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 4e5+5;
int rs[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q, x; cin >> q >> x;
    set<pair<int,int>> ms;
    for (int i = 0; i < x; i++) ms.insert({0,i});
    while (q--) {
        int y; cin >> y;
        y %= x;
        ms.erase({rs[y],y});
        rs[y]++;
        ms.insert({rs[y],y});
        auto p = *ms.begin();
        cout << (p.first*x+p.second) << '\n';
    }
}
