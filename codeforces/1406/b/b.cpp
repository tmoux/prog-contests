#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
const ll INV = -1e18;
int n;
ll a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        bool has0 = false;
        vector<ll> vpos, vneg;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            if (a[i] == 0) has0 = true;
            else if (a[i] < 0) {
                vneg.push_back(a[i]);
            }
            else if (a[i] > 0) {
                vpos.push_back(a[i]);
            }
        }
        sort(vpos.begin(),vpos.end());
        sort(vneg.begin(),vneg.end());
        reverse(vneg.begin(),vneg.end());
        
        ll ans = has0 ? 0 : INV;
        for (int neg = 0; neg <= 5; neg++) {
            int pos = 5-neg;
            if (neg <= vneg.size() && pos <= vpos.size()) {
                ll tr = 1;
                if (neg % 2 == 0) {
                    for (int i = 1; i <= neg; i++) {
                        tr *= vneg[vneg.size()-i];
                    }
                    for (int i = 1; i <= pos; i++) {
                        tr *= vpos[vpos.size()-i];
                    }
                }
                else {
                    for (int i = 0; i < neg; i++) {
                        tr *= vneg[i];
                    }
                    for (int i = 0; i < pos; i++) {
                        tr *= vpos[i];
                    }
                }
                ans = max(ans,tr);
            }
        }
        cout << ans << '\n';
    }
}
