#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> a[i];
    ll sum = 0;
    ll xxor = 0;
    for (int i = 0; i < N; i++) {
        sum += a[i];
        xxor ^= a[i];
    }
    cout << (sum-xxor) << '\n';

    return 0;
}

