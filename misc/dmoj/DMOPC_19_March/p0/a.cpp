#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    vector<int> v;
    for (int i = 0; i < 3; i++) {
        int ai; cin >> ai;
        v.push_back(ai);
    }
    sort(v.begin(),v.end());
    cout << (v[0]+v[1] > v[2] ? "yes" : "no") << '\n';
}

