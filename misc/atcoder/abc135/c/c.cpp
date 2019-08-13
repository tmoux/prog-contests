#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, A[maxn], B[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N+1; i++) {
        cin >> A[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> B[i];
    }
    ll ans = 0;
    for (int i = N; i >= 1; i--) {
        ll d = min(A[i+1],B[i]);
        A[i+1] -= d;
        B[i] -= d;
        ans += d;
        d = min(A[i],B[i]);
        A[i] -= d;
        B[i] -= d;
        ans += d;
    }
    cout << ans << '\n';
}

