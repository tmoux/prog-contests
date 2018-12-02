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

const int M = 1e9+7;
namespace fen {
    void add(int bit[], int i, int x) {
        for (; i <= n; i += i & (-i))
            bit[i] = (bit[i]+x) % M;
    }

    int sum(int bit[], int i) {
        int r = 0;
        for (; i; i -= i & (-i)) {
            r = (r+bit[i]) % M;
        }
        return r;
    }
}
  
const int maxn = 755;
int R, C, K, a[maxn][maxn]; //a is one-indexed
int cols[maxn]; //each column is a BIT
map<int,ordered_set<int>> numCounts; //pbds for each number
    
int main()
{
    cin >> R >> C >> K;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = n; j >= 1; j--) {
            int adding = (fen::sum(cols,n) - fen::sum(cols,j) + M) % M;
        }
    }
}



