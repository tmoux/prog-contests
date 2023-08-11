#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, k;
int a[maxn];
bool need[maxn];

int bit[maxn];
void add(int i, int x) {
    for (; i <= n; i += i & (-i))
        bit[i] += x;
}

int sum(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r += bit[i];
    }
    return r;
}

int bit_max[maxn];
void add_max(int i, int x) {
    for (; i <= n; i += i & (-i))
        bit_max[i] = max(bit_max[i],x);
}

int query_max(int i) {
    int r = 0;
    for (; i; i -= i & (-i)) {
        r = max(r,bit_max[i]);
    }
    return r;
}

int bit_min[maxn];
void add_min(int i, int x) {
    for (; i <= n; i += i & (-i))
        bit_min[i] = x;
}

int query_min(int i) {
    int r = n+1;
    for (; i; i -= i & (-i)) {
        r = min(r,bit_min[i]);
    }
    return r;
}

pair<int,int> range[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < k; i++) {
        int bi; cin >> bi;
        need[bi] = true;
    }
    for (int i = 1; i <= n; i++) {
        add_min(i,n+1);
    }
    for (int i = 1; i <= n; i++) {
        if (need[a[i]]) add_min(a[i],i);
    }
    vector<pair<int,int>> v;
    for (int i = 1; i <= n; i++) {
        if (need[a[i]]) {
            add_min(a[i],n+1);
            add_max(a[i],i);
        }
        else {
            int l = query_max(a[i]-1)+1;
            int r = query_min(a[i]-1)-1;
            range[i] = {l,r};
            v.push_back({a[i],i});
        }
    }
    sort(v.begin(),v.end()); 
    ll ans = 0;
    Node *root = new Node(1,n);
    for (auto p: v) {
        int ai = p.first;
        int i = p.second;
        ans += range[i].second-range[i].first+1-(sum(range[i].second)-sum(range[i].first-1));
        add(i,1);
    }
    cout << ans << '\n';
}
