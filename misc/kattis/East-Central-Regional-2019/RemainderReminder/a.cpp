#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int inv(int a, int m) {
    for (int i = 1; i < m; i++) {
        if ((1LL*i*a) % m == 1) return i;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b, c, d, e, f, g; cin >> a >> b >> c >> d >> e >> f >> g;
    vector<int> v;
    for (int i = 1; a-2*i > 0; i++) {
        int vol = (a-2*i)*(b-2*i)*i;
        v.push_back(vol);
    }
    sort(v.rbegin(),v.rend());
    vector<int> yi = {v[1]*v[2],v[0]*v[2],v[0]*v[1]};
}

