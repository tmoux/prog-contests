#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<int> ans;
        for (ll = i = 1; i <= n/2; ++i) {
            ll start = i;
            ll end = n/2;
            ll key = n/i;
            ll last = -1;
            while (start <= end) {
                ll mid = (start+end)/(2LL);
                if (n/mid == key) {
                    last = mid;
                    start = mid+1;
                }
                else if (n/mid > key) {
                    start = mid+1;
                }
                else {
                    end = mid-1;
                }
            }
            ans.emplace_back(key);
            i = last;
        }
        ans.emplace_back(1);
    }
}

