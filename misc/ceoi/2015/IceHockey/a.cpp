#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int maxn = 40;
 
int N;
ll M;
ll A[maxn], B[maxn];
 
int main()
{
	cin >> N >> M;
    ll tot = 0;
	int split = N/2;
	for (int i = 0; i < split; i++) {
		cin >> A[i];
        tot += A[i];
	}
    for (int i = split; i < N; i++) {
        cin >> B[i-split];
        tot += B[i-split];
    }
    if (tot <= M) {
        cout << (1LL<<N) << '\n';
        return 0;
    }
    vector<ll> as;
	for (int i = 0; i < (1<<split); i++) {
        ll total = 0;
        for (int j = 0; j < split; j++) {
            if (i & (1<<j)) total += A[j];
            if (total > M) {
                break;
            }
        }
        if (total <= M) as.push_back(total);
    }
    sort(as.begin(),as.end());
 
    ll ans = 0;
    for (int i = 0; i < (1<<(N-split)); i++) {
        ll total = 0;
        for (int j = 0; j < N-split; j++) {
            if (i & (1<<j)) total += B[j];
            if (total > M) {
                break;
            }
        }
        if (total <= M) {
            auto it = upper_bound(as.begin(),as.end(),M-total);
            ans += distance(as.begin(),it);
        }
    }
    cout << ans << '\n';
}
