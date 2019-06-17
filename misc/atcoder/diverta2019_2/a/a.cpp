#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N, K; cin >> N >> K;
    if (K == 1) {
        cout << 0 << '\n';
    }
    else cout << (N-K) << '\n';
}

