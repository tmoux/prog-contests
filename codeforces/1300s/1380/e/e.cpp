#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m;
set<int>* s[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        s[i] = new set<int>;
    }
    for (int i = 1; i <= n; i++) {
        int ti; cin >> ti;
        s[ti]->insert(i);
    }
    int num_cons = 0;
    for (int i = 1; i <= m; i++) {
        for (auto j: (*s[i])) {
            if (s[i]->count(j-1)) {
                num_cons++;
            }
        }
    }
    cout << (n-1-num_cons) << '\n';
    for (int i = 0; i < m-1; i++) {
        int a, b; cin >> a >> b;
        if (s[a]->size() < s[b]->size()) swap(s[a],s[b]);
        for (auto j: (*s[b])) {
            if (s[a]->count(j-1)) num_cons++;
            if (s[a]->count(j+1)) num_cons++;
        }
        for (auto j: (*s[b])) {
            s[a]->insert(j);
        }
        cout << (n-1-num_cons) << '\n';
    }
}
