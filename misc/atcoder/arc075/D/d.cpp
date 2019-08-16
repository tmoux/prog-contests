#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, A, B;
ll h[maxn];

ll ceil(ll a, ll b) {
    return a%b==0?a/b:a/b+1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> A >> B;
    for (int i = 0; i < N; i++) {
        cin >> h[i];
    }
    sort(h,h+N);
    int lo = 0, hi = 1e9+9;
    ll diff = A - B;
    while (lo + 1 < hi) {
        ll mid = (lo + hi) >> 1;
        vector<ll> v;
        for (int i = 0; i < N; i++) {
            if (h[i] - B * mid > 0) {
                v.push_back(h[i]-B*mid);
            }
        }
        ll cnt = mid;
        for (ll i: v) {
            cnt -= ceil(i,diff);            
        }
        if (cnt < 0) {
            lo = mid;
        }
        else hi = mid;
    }
    cout << hi << '\n';
}

