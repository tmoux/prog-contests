#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n; 
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            if (i % 2 == 0 && ai < 0) ai *= -1;
            else if (i % 2 == 1 && ai > 0) ai *= -1;
            cout << ai << ' ';
        }
        cout << '\n';
    }
}

