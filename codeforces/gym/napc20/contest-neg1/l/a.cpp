#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    set<int> s;
    for (int i = 1; i < n; i++) {
        //cout << i << ' ' << n/i << ' ' << (n-(n/i)*i) << '\n';
        s.insert(n%i);
    }
    cout << s.size() << '\n';
}
