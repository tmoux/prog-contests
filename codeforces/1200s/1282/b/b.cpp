#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, p, k;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n >> p >> k;
        vector<int> a(n);
        vector<ll> pre(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(),a.end());
        pre[0] = a[0];
        for (int i = 1; i < n; i++) {
            pre[i] = pre[i-1] + a[i];
        }
        /*
        for (int i = 0; i < n; i++) {
            cout << pre[i] << ' ';
        }
        cout << '\n';
        */
        int maxans = 0;
        for (int i = 0; i < k; i++) {
            ll curr = i==0?0:pre[i-1];
            //cout << i << ": " << curr << '\n';
            if (curr > p) continue;
            int tr = i;
            for (int j = i+k-1; j < n; j += k) {
                curr += a[j];
                //cout << i << ": " << curr << endl;
                if (curr > p) break;
                tr += k;
            }
            maxans = max(maxans,tr);
        }
        cout << maxans << '\n';
    }
}

