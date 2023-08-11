#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool has[55][10005];
int n;

bool disjoint(int a, int b) {
    
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int m; cin >> m >> n;
    vector<set<int>> s(m);
    for (int i = 0; i < m; i++) {
        int k; cin >> k;
        while (k--) {
            int ai; cin >> ai;
            s[i].insert(ai);
        }
    }
    bool poss = true;
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (disjoint(s[i],s[j])) {
                poss = false;
                break;
            }
        }
    }
    cout << (poss ? "possible" : "impossible") << '\n';
}

