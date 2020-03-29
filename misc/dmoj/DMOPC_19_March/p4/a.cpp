#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using ll = long long;

template <class K, class V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<K, V, std::less<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
/* order_of_key(k), how many elements <k */
/* find_by_order(k), k'th element (from 0) */
/* both logn */

const int maxn = 5e5+5;
ordered_set<int> mp[2*maxn+20];
int a[maxn];
int N, Q;

void upd(int i, int del) {
    mp[maxn+a[i]].erase(i);
    a[i] += del;
    mp[maxn+a[i]].insert(i);
}

int query(int l, int r, int c) {
    int res = mp[maxn+c].order_of_key(r+1);
    res -= mp[maxn+c].order_of_key(l);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        mp[maxn+a[i]].insert(i);
    }
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int x; cin >> x;
            upd(x,1);
        }
        else if (t == 2) {
            int x; cin >> x;
            upd(x,-1);
        }
        else {
            int l, r, c; cin >> l >> r >> c;
            cout << query(l,r,c) << '\n';
        }
    }
}
