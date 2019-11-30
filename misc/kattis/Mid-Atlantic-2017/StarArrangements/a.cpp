#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool poss(int n, int i, int j) {
    return (n % (i+j) == 0) ||
           ((n-i) % (i+j) == 0);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<pair<int,int>> ans;
    for (int i = 2; i < n; i++) {
        for (int j = i-1; j <= i; j++) {
            if (poss(n,i,j)) {
                ans.push_back({i,j});
            }
        }
    }
    cout << n << ":\n";
    for (auto p: ans) {
        cout << p.first << "," << p.second << '\n';
    }
}

