#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
bool eq(vector<int> a, vector<int> b) {
    for (int j = 0; j < n; j++) {
        if (a[j] != b[j]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<int> p(n), q(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> q[i];
    }
    vector<int> pe;
    for (int j = 0; j < n; j++) {
        pe.push_back(j+1);
    }
    int pt = 0;
    int a = -1, b = -1;
    do {
        if (eq(p,pe)) {
            a = pt;
        }
        if (eq(q,pe)) {
            b = pt;
        }
        pt++;
    } while (next_permutation(pe.begin(),pe.end()));
    assert(a != -1 && b != -1);
    //cout << a << ' ' << b << '\n';
    cout << abs(a-b) << '\n';
}

