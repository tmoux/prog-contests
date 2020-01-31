#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m, k;
int a[maxn];
ll cnt[1<<20];

ll ans = 0;
ll ch2(ll x) {
    return (1LL*x*(x-1))/2;
}
void upd(int x, int v) {
    if (k != 0) {
        ans -= cnt[x]*cnt[x^k];
        cnt[x] += v;
        ans += cnt[x]*cnt[x^k];
    }
    else {
        ans -= ch2(cnt[x]);
        cnt[x] += v;
        ans += ch2(cnt[x]);
    }
}

ll res[maxn];

int brute(int l, int r) {
    int ans = 0;
    for (int i = l+1; i <= r; i++) {
        for (int j = i; j <= r; j++) {
            if ((a[j]^a[i-1]) == k) {
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] ^= a[i-1];
    }
    vector<pair<pair<int,int>,pair<int,int>>> qs;
    int blk = 350;
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        l--;
        qs.push_back({{l/blk,i},{l,r}});
    }
    sort(qs.begin(),qs.end(),[](auto a, auto b) {
        return a.first.first != b.first.first ? a.first.first < b.first.first : a.second.second < b.second.second; 
        });
    int L = 0, R = 0;
    for (auto q: qs) {
        int l = q.second.first;
        int r = q.second.second;
        //cout << l << ' ' << r << endl;
        while (L <= l) {
            upd(a[L],-1);
            L++;
        }
        while (L > l) {
            upd(a[L-1],1);
            L--;
        }
        while (R <= r) {
            upd(a[R],1);
            R++;
        }
        while (R > r+1) {
            upd(a[R-1],-1);
            R--;
        }
        /*
        for (int i = 0; i <= 10; i++) {
            cout << i << ": " << cnt[i] << endl;
        }
        */
        //cout << l << ' ' << r << ": " << ans << ", " << brute(l,r) << endl;
        //assert(ans == brute(l,r));
        //cout << q.first.second << endl;
        res[q.first.second] = ans;
    }
    for (int i = 0; i < m; i++) {
        cout << res[i] << '\n';
    }
}
