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
map<int,ordered_set<int>> adds, removes;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    while (n--) {
        int a, t, x; cin >> a >> t >> x;
        if (a == 1) {
            adds[x].insert(t);
        }
        else if (a == 2) {
            removes[x].insert(t);
        }
        else if (a == 3) {
            int ans = adds[x].order_of_key(t) - removes[x].order_of_key(t); 
            cout << ans << '\n';
        }
    }
}

