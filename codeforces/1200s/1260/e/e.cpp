#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1<<19;
//n = 2^i, there are i rounds in total
//each round, half the people die
//configuration is determined by starting bracket configuration
//maybe that's not that useful?
//Let 2^m <= n, 2^(m+1) > n,
//then we can win m rounds by ourselves
//of the people above us, we want the ones with high cost to die
//before they reach us
//
int n, a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];

    }
}

