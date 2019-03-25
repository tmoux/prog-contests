#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int maxn = 2e4+5;
int v[maxn];
ll pre[maxn];
ld f[100000];

void solve(int t) {
    memset(v,0,sizeof v);
    memset(pre,0,sizeof pre);
    int N, K; cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> v[i];
    sort(v,v+N);
    pre[0] = v[0];
    for (int i = 1; i < N; i++) pre[i] = v[i] + pre[i-1];
    f[0] = (ld) pre[N-1] / N;
    int pt = 0; //pt points to the smallest index that is larger than f[i-1]
    for (int i = 1; i <= K; i++) {
        while (pt < N && v[pt] <= f[i-1]) pt++;
        ld s1 = pt*f[i-1];
        ld s2 = 1LL*(pre[N-1] - (pt==0?0:pre[pt-1]));
        f[i] = (s1+s2)/N;
        //cout << i << ": " << f[i] << ' ' << (s1+s2) << '\n';
    }

    /*
    for (int i = 0; i <= K; i++) {
        cout << i << ": " << f[i] << '\n';
    }
    */
    cout << "Case #" << t << ": " << f[K] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(12);
    int t; cin >> t;
    for (int a = 1; a <= t; a++) solve(a);
}

