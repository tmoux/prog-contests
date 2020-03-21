#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        set<int> s;
        while (n--) {
            int ai; cin >> ai;
            s.insert(ai);
        }
        cout << s.size() << '\n';
    }
}
