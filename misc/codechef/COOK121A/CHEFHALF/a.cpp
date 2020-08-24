#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
int a[maxn];
int b[maxn];
int pos[maxn];

set<int> s[2];
int get_next(int i) {
    int c = b[i];
    auto it = s[c^1].upper_bound(i);
    if (it == s[c^1].end()) return n;
    return *it;
}
int get_prev(int i) {
    int c = b[i];
    auto it = s[c^1].lower_bound(i);
    if (it == s[c^1].begin()) return -1;
    --it;
    return *it;
}
void solve() {
    cin >> n;
    vector<int> v;
    s[0].clear();
    s[1].clear();
    vector<int> aa(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    map<int,int> compress;
    int pt = 1;
    for (auto i: v) {
        compress[i] = pt++;
    }
    for (int i = 0; i < n; i++) {
        a[i] = compress[a[i]];
        pos[a[i]] = i;
        b[i] = 1;
        s[1].insert(i);
    }
    for (auto& i: v) {
        i = compress[i];
    }
    ll ans = 0;
    for (int i: v) {
        b[pos[i]] = 0;        
        s[1].erase(pos[i]);
        s[0].insert(pos[i]);
        int L = get_prev(pos[i]);
        int R = get_next(pos[i]);
        int range0 = R-L-1;
        int rangeL = L - get_prev(L);
        int rangeR = get_next(R) - R;
        /*
        for (int j = 0; j < n; j++) {
            cout << b[j];
        }
        cout << '\n';
        cout << i << ": " << rangeL << ' ' << range0 << ' ' << rangeR << '\n';
        */
        ans += min(rangeR,range0) - min(rangeR,R-pos[i]-1);
        ans += min(rangeL,range0) - min(rangeL,pos[i]-L-1);
        if (rangeL + rangeR >= range0) {
            if (rangeL > rangeR) swap(rangeL,rangeR);
            int lo = max(1,range0-rangeR);
            int hi = min(rangeL,range0-1);
            ans += max(0,hi-lo+1);
        }
        //cout << i << ": curans = " << ans << '\n';
    }
    reverse(v.begin(),v.end());
    for (int i: v) {
        b[pos[i]] = 1;
        s[0].erase(pos[i]);
        s[1].insert(pos[i]);
        int L = get_prev(pos[i]);
        int R = get_next(pos[i]);
        int range0 = R-L-1;
        int rangeL = L - get_prev(L);
        int rangeR = get_next(R) - R;
        if (rangeL + rangeR >= range0) {
            if (rangeL > rangeR) swap(rangeL,rangeR);
            int lo = max(1,range0-rangeR);
            int hi = min(rangeL,range0-1);
            ans += max(0,hi-lo+1);
        }
        //cout << i << ": curans = " << ans << '\n';
    }
    cout << ans << '\n';
}

void brute() {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if ((j-i+1) % 2 != 0) continue;
            vector<int> v;
            for (int k = i; k <= j; k++) {
                v.push_back(a[k]);
            }
            bool flag = false;
            int sz = (j-i+1)/2;
            for (int k = 0; k < sz*2; k++) {
                int small = 0;
                for (int i = 0; i < sz; i++) {
                    small = max(small,v[i]);
                }
                int big = 2e9;
                for (int i = sz; i < v.size(); i++) {
                    big = min(big,v[i]);
                }
                if (small < big) {
                    flag = true;
                    break;
                }
                
                rotate(v.begin(),v.begin()+1,v.end());
            }
            if (flag) {
                cout << "found " << i << ' ' << j << '\n';
                ans++;
            }
        }
    }
    cout << "brute: " << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
        //brute();
    }
}
