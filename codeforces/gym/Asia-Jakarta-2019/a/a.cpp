#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        cout << (n+1-ai) << ' ';
    }
    cout << '\n';
}

