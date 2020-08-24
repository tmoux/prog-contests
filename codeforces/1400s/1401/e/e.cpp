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

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
		}
		else {
			l = NULL;
			r = NULL;
		}
	}

	void add(int i, int x) {
		if (s == e) {
			sum += x;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		sum = l->sum + r->sum;
	}

	int getsum(int st, int en) {
		if (st <= s && e <= en) {
			return sum;
		}
		int ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};

const int maxn = 1e5+5, maxx = 1e6+6;
int n, m;
pair<int,int> horiz[maxx];
vector<int> start[maxx], stop[maxx];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i <= 1000000; i++) {
        horiz[i] = {-1,-1};
    }
    ll ans = 1;
    for (int i = 0; i < n; i++) {
        int y, lx, rx; cin >> y >> lx >> rx;
        start[lx].push_back(y);
        stop[rx].push_back(y);
        if (lx == 0 && rx == 1000000) ans++;
    }
    for (int i = 0; i < m; i++) {
        int x, ly, ry; cin >> x >> ly >> ry;
        horiz[x] = {ly,ry};
        if (ly == 0 && ry == 1000000) ans++;
    }
    Node *root = new Node(0,1000000);
    for (int x = 0; x <= 1000000; x++) {
        for (int y: start[x]) {
            root->add(y,1);
        }

        if (horiz[x].first != -1) {
            ans += root->getsum(horiz[x].first,horiz[x].second);
        }

        for (int y: stop[x]) {
            root->add(y,-1);
        }
    }
    cout << ans << '\n';
}
