#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    int p1 = 0, p2 = 1;
    int rot = 0;
    while (q--) {
        int t; cin >> t;
        if (t == 2) {
            //p1 = (p1&1)?(p1-1+n)%n:(p1+1)%n;
            //p2 = (p2&1)?(p2-1+n)%n:(p2+1)%n;
            swap(p1,p2);
        }
        else {
            int x; cin >> x;
            p1 = (p1+x+n) % n;
            p2 = (p2+x+n) % n;
        }
    }
    vector<int> v(n);
    for (int i = p1, a = 1; ; a += 2) {
        v[i] = a;
        i = (i+2)%n;
        if (i == p1) break;
    }
    for (int i = p2, a = 2; ; a += 2) {
        v[i] = a;
        i = (i+2)%n;
        if (i == p2) break;
    }
    for (auto i: v) {
        cout << i << ' ';
    }
    cout << '\n';
}
