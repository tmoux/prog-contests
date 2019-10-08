#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll M, N; cin >> M >> N;
    ll gc = __gcd(N,M);
    M /= gc;
    N /= gc;
    cout << ((N&1 && M&1) ? gc : 0) << '\n';
}

