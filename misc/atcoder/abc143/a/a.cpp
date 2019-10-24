#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b; cin >> a >> b;
    cout << max(0,a-2*b) << '\n';
}

