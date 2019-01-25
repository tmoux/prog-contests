#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, T, m[maxn], b[maxn];

int main()
{
    freopen("cowjog.in","r",stdin); freopen("cowjog.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> T;
    for (int i = 0; i < N; i++) {
        cin >> b[i] >> m[i];
    }
    int ans = N;
    ll t = 1LL*T*m[N-1] + b[N-1];
    for (int i = N - 2; i >= 0; i--) {
        ll t2 = 1LL*T*m[i] + b[i];
        if (t2 >= t) --ans;
        t = min(t,t2);
    }
    cout << ans << '\n';
    return 0;
}

