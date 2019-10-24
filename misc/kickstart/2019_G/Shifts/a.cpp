#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using ll = long long;

const int N = 21;
template <class K, class V = __gnu_pbds::null_type>
using ordered_multiset = __gnu_pbds::tree<K, V, std::less_equal<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    /*
    ordered_multiset<int> ms;
    ms.insert(5);
    ms.insert(5);
    ms.insert(5);
    ms.insert(5);
    ms.insert(3);
    ms.insert(8);
    cout << ms.order_of_key(6) << '\n';
    return 0;
    */
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";
        int n; ll H; cin >> n >> H;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        ordered_multiset<ll> ms;
        vector<pair<ll,ll>> points;
        for (int i = 0; i < (1<<(n/2)); i++) {
            for (int j = 0; j < (1<<(n/2)); j++) {
                if ((i|j) == (1<<(n/2))-1) {
                    pair<ll,ll> p;
                    for (int k = 0; k < n/2; k++) {
                        if (i & (1<<k)) p.first += a[k];
                        if (j & (1<<k)) p.second += b[k];
                    }
                    points.push_back({H-p.first,H-p.second});
                }
            }
        }

        vector<pair<ll,ll>> p2;
        int nh = n-n/2;
        for (int i = 0; i < (1<<nh); i++) {
            for (int j = 0; j < (1<<nh); j++) {
                if ((i|j) == (1<<nh)-1) {
                    pair<ll,ll> p;
                    for (int k = 0; k < nh; k++) {
                        if (i & (1<<k)) p.first += a[k+n/2];
                        if (j & (1<<k)) p.second += b[k+n/2];
                    }
                    p2.push_back(p);
                    //cout << p.first << ' ' << p.second << '\n';
                }
            }
        }
        
        sort(points.begin(),points.end(),[](auto a, auto b) {
                if (a.first != b.first) return a.first > b.first;
                return a.second > b.second;
                });
        sort(p2.begin(),p2.end(),[](auto a, auto b) {
                if (a.first != b.first) return a.first < b.first;
                return a.second < b.second;
                });
        ll ans = 0;
        for (auto p: p2) {
            //cout << p.first << ' ' << p.second << '\n';
            while (!points.empty() && points.back().first <= p.first) {
                ms.insert(points.back().second);
                points.pop_back();
            }
            /*
            cout << "points:\n";
            for (auto pp: ms) {
                cout << pp << '\n';
            }
            */
            ans += ms.order_of_key(p.second+1);
        }
        cout << ans << '\n';
    }
}

