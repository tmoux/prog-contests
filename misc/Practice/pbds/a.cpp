#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

typedef long long ll;

template <class K, class V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<K, V, std::less<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
// order_of_key(k), how many elements < k 
// find_by_order(k), k'th element (from 0) 
// both logn 

int main()
{
    ordered_set<int> a;            
    for (int i = 1; i <= 100000; i++) {
        a.insert(i);
    }
    cout << a.size() << '\n';
    cout << a.order_of_key(17) << '\n';
}

