#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using ll = long long;

template <class K, class V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<K, V, std::less<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

struct SegDyn
{
	int s, e, m; //represents range [s,e]
	SegDyn *l, *r;
	ll sum; //sum for this interval
	SegDyn(int _s, int _e) {
		s = _s;
		e = _e;
		m = (s+e)/2;
		l = NULL;
		r = NULL;
		sum = 0;
	}

	void prepareL() { if (l == NULL) l = new SegDyn(s,m); }
	void prepareR() { if (r == NULL) r = new SegDyn(m+1,e); }

	void pull() {
		sum = 0;
		if (l) sum += l->sum;
		if (r) sum += r->sum;
	}

	void add(int idx, int del) { //a[idx] += del
		if (s == e && s == idx) {
			//at the node, stop
			sum += del;
			return;
		}
		if (idx <= m) {
			prepareL();
			l->add(idx,del);
		}
		else {
			prepareR();
			r->add(idx,del);
		}
		pull(); //updates current node based on the children
	}

	ll getsum(int se, int en) {
		if (se <= s && e <= en) return sum;
		ll res = 0;
		if (l && se <= m) res += l->getsum(se,en);
		if (r && en > m) res += r->getsum(se,en);
		return res;	
	}
};

const int maxn = 2e5+5;

//ans is sum of all
//if all L's, then add top (sz-1)
//else Let cb be number of L's. 
//If top cb is all L's, then add top (cb-1) plus top F
//Else, add top cb

ordered_set<int> os;
SegDyn *seg = new SegDyn(1,1000000000);

ll top_x(int x) {
    if (x == 0) return 0LL;
    int n = os.size();
    int mn = *os.find_by_order(n-x);
    return seg->getsum(mn,1000000000);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    set<int> F, L;
    ll tot = 0;
    for (int iter = 0; iter < n; iter++) {
        ll ans = -1;
        int t, d; cin >> t >> d;
        tot += d;
        if (d < 0) {
            d *= -1;
            seg->add(d,-d);
            if (t == 0) F.erase(d);
            else L.erase(d);
            os.erase(d);
        }
        else {
            if (t == 0) F.insert(d);
            else L.insert(d);
            seg->add(d,d);
            os.insert(d);
        }
        if (L.size() == os.size()) {
            ans = tot + tot - *L.begin();
        }
        else {
            if (L.empty()) {
                ans = tot;
            }
            else {
                assert(!L.empty() && !F.empty());
                int cb = L.size();
                if (*L.begin() > *F.rbegin()) {
                    ans = tot + top_x(cb-1) + *F.rbegin();
                }
                else {
                    ans = tot + top_x(cb);
                }
            }
        }
        assert(ans != -1);
        cout << ans << '\n';
    }
}
