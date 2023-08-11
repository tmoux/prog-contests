#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int pre[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; scanf("%d %d",&n,&q);
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        scanf("%d",&A[i]);
    }
    while (q--) {
        int l, r; scanf("%d %d",&l,&r);
        pre[l]++;
        pre[r+1]--;
    }
    vector<int> freqs;
    for (int i = 1; i <= n; i++) {
        pre[i] += pre[i-1];
        freqs.push_back(pre[i]);
    }
    sort(freqs.begin(),freqs.end(),greater<int>());
    sort(A.begin(),A.end(),greater<int>());
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (ll)(freqs[i])*A[i];
    }
    printf("%I64d\n",ans);

    return 0;
}
	

