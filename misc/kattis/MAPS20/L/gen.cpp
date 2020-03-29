#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    int n, m; cin >> n >> m;
    cout << n << ' ' << m << '\n';
    set<pair<int,int>> s;
    while (m) {
        int a = gen() % n;
        int b = gen() % n;
        if (a == b || s.count({a,b})) continue;
        s.insert({a,b});
        cout << a << ' ' << b << '\n';
        m--;
    }
}

