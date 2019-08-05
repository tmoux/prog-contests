#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
 * fast queries (few updates): 
 *      after each update, simply recompute all orders and 
 *      queries in O(1)
 *
 * fast updates (few queries):
 *      Give everyone enough space initally (5e5,2*5e5,3*5e5,...,10*5e5,10*5e5+1)
 *      Save each update, then before each query, recompute all orders and
 *      answer the query.
*/

const int maxn = 250005;
const int maxq = 5e5+5;
const ll INF = 1LL<<62;
int N, Q;
int d[maxn];
ll a[maxn];
int start;
int ans[maxn];
vector<int> v;

int ord[maxn];

void calcans() {
    int t = 1;
    int l = start, r = start;
    while (l != 1 || r != N) {
        if (l == 1) {
            ans[r+1] = t;
            r++;
        }
        else if (r == N) {
            ans[l-1] = t;
            l--;
        }
        else {
            if (ord[l-1] > ord[r+1]) {
                ans[l-1] = t;
                l--;
            }
            else {
                ans[r+1] = t;
                r++;
            }
        }
        t++;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> start;
    vector<pair<int,int>> ps;
    for (int i = 1; i <= N; i++) {
        cin >> d[i];
        ps.push_back({d[i],i});
    }
    sort(ps.begin(),ps.end(),greater<pair<int,int>>());
    int t = 0;
    multiset<ll> ms;
    for (auto p: ps) {
        v.push_back(p.second);
        ord[p.second] = t;
        t++;
    }
    calcans();
    for (int i = 1; i <= N; i++) {
        cout << i << ": " << ans[i] << '\n';
    }

    cin >> Q;
    while (Q--) {
        char c; cin >> c;
        if (c == 'E') { //update
            int i, e; cin >> i >> e;
            v.erase(find(v.begin(),v.end(),i));
            v.insert(v.begin()+e-1,i);

            for (int t = 0; t < v.size(); t++) {
                ord[v[t]] = t;
            }
            calcans();
        }
        else { //query
            int b; cin >> b;
            cout << ans[b] << '\n';
        }
    }
}
