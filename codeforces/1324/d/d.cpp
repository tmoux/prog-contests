#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template <class K, class V = __gnu_pbds::null_type>
using ordered_multiset = __gnu_pbds::tree<K, V, std::less_equal<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
/* order_of_key(k), how many elements <k */
/* find_by_order(k), k'th element (from 0) */
/* both logn */

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    ordered_multiset<ll> ms;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += ms.order_of_key(a[i]-b[i]); 
        ms.insert(b[i]-a[i]);
    }
    cout << ans << endl;
}
