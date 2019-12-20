#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
int cnt[maxn];

int l[maxn], d[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    map<int,vector<int>> mp;
    int tot = 0;
    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    for (int i = 0; i < n; i++) {
        mp[l[i]].push_back(d[i]);
        tot += d[i];
    }
    int ans = 1e9+9;
    for (auto p: mp) {
        vector<int>& v = p.second;
        for (int i: v) {
            tot -= i;
        }
        int need = v.size()-1;
        int cur = 0;
        int pt = 200;
        int tr = tot;
        while (cur < need && pt >= 1) {
            int add = min(cnt[pt],need-cur);
            cur += add;
            tr -= add*pt;
            pt--;
        }
        ans = min(ans,tr);
        //cout << p.first << ": " << tr << '\n';
        
        for (int i: v) {
            cnt[i]++;
            tot += i;
        }
    }
    cout << ans << '\n';
}

