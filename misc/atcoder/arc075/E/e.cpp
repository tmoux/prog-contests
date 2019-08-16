#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int N, K, a[maxn];
//how many subarrays have sum >= 0?
ll pre[maxn];

template <class K, class V = __gnu_pbds::null_type>
using ordered_multiset = __gnu_pbds::tree<K, V, std::less_equal<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        a[i] -= K;
        pre[i] = pre[i-1] + a[i];
    }
    ordered_multiset<ll> ms;
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        ms.insert(pre[i-1]);
        ans += ms.order_of_key(pre[i]+1);
    }
    cout << ans << '\n';
}

