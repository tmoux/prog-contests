#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, a[maxn];
int ans[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("equal.in","r",stdin); freopen("equal.out","w",stdout);
    cin >> n;
    map<int,int> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ++mp[a[i]];
    }
    vector<pair<int,int>> v;
    for (auto p: mp) {
        v.push_back(p);
    }
    sort(v.begin(),v.end(),[](auto a, auto b) {
        return a.second < b.second;
        });
    int cur = 0;
    int d = mp.size();
    for (int i = 0; i <= n; i++) ans[i] = maxn;
    ans[0] = d;
    ans[n] = 1;
    int cnt = 0;
    int tot = 0;
    for (auto p: v) {
        cnt++;
        tot += p.second;
        bool found = false;
        for (int i = 2*p.first; i <= 1000000; i += p.first) {
            if (mp.count(i)) {
                found = true;
                break;
            }
        }
        //cout << p.first << ": " << found << endl;
        if (found) {
            cur += p.second;
            d--;
            ans[cur] = min(ans[cur],d);
        }
        ans[tot] = min(ans[tot],(int)v.size()-cnt+1);
    }
    for (int i = 1; i <= n; i++) {
        ans[i] = min(ans[i],ans[i-1]);
    }
    for (int i = 0; i <= n; i++) {
        cout << ans[i] << " \n"[i==n];
    }
}
