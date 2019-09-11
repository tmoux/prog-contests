#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N; cin >> N;
    ll ans = (1LL*N*(N+1))/2 - N;
    cout << ans << '\n';
}

