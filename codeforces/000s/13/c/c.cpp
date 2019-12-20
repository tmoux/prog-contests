#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
const int INF = 1e9+9;
int n;
ll a[maxn];

void amin(ll& a, ll b) {
    a = min(a,b);
}

ll dp[2][maxn];
map<int,int> mp;
vector<int> vals;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        vals.push_back(a[i]);
    }
    sort(vals.begin(),vals.end());
    for (int i = 1; i <= n; i++) {
        int k = i&1;
        ll mn = 1e18;
        for (int j = 0; j < n; j++) {
            mn = min(mn,abs(a[i]-vals[j])+dp[k^1][j]);
            dp[k][j] = mn;
            //cout << i << ' ' << vals[j] << ": " << dp[k][j] << '\n';
            
            if (j < n-1) {
                if (vals[j] < a[i]) {
                    mn -= vals[j+1]-vals[j];
                }
                else {
                    mn += vals[j+1]-vals[j];
                }
            }
        }
        //cout << '\n';
    }
    ll ans = 1e18;
    for (int j = 0; j < n; j++) {
        amin(ans,dp[n&1][j]);
    }
    cout << ans << '\n';
}

