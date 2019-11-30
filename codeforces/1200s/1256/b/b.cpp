#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve(vector<int>& v, int i) {
    if (i >= v.size()-1) return;
    pair<int,int> mn = {105,-1};
    for (int j = i; j < v.size(); j++) {
        mn = min(mn,{v[j],j});
    }
    for (int j = mn.second - 1; j >= i; j--) {
        swap(v[j],v[j+1]);
    }
    solve(v,max(i+1,mn.second));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        solve(v,0);
        for (int i: v) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}

