#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N, M; cin >> N >> M;
    set<string> s;
    for (int i = 0; i < N; i++) {
        string si; cin >> si;
        s.insert(si);
    }
    int ans = 0;
    while (M--) {
        int ti; cin >> ti;
        bool poss = true;
        while (ti--) {
            string si; cin >> si;
            if (!s.count(si)) {
                poss = false;
            }
        }
        if (poss) ans++;
    }
    cout << ans << endl;
}

