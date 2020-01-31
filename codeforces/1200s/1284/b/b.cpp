#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+5;
int n, s[maxn];
bool is[maxn];

vector<pair<int,int>> st, en;
int cnt[maxn];
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int l; cin >> l;
        vector<int> v;
        while (l--) {
            int x; cin >> x;
            v.push_back(x);
        }
        bool good = false;
        for (int i = 0; i < v.size()-1; i++) {
            if (v[i] < v[i+1]) {
                good = true;
                break;
            }
        }
        if (!good) {
            st.push_back({v.back(),v[0]});
            cnt[v[0]]++;
        }
    }
    for (int i = 1; i <= 1000000; i++) {
        cnt[i] += cnt[i-1];
    }
    ll ans = 1LL*n*n;
    for (auto p: st) {
        ans -= cnt[p.first];
    }
    cout << ans << '\n';
}

