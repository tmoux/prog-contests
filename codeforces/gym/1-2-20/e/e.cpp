#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

const int maxn = 1e5+5;
int n, s[maxn], q;
map<int,vector<int>> mp;

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
            sum = x;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		sum = __gcd(l->sum,r->sum);
	}

	int getsum(int st, int en) {
		if (st <= s && e <= en) {
			return sum;
		}
		int ret = 0;
		if (st <= m) {
			ret = __gcd(ret,l->getsum(st,en));
		}
		if (en > m) {
			ret = __gcd(ret,r->getsum(st,en));
		}
		return ret;
	}
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    Node *root = new Node(1,n);
    for (int i = 1; i <= n; i++) {
        int si; cin >> si;
        root->add(i,si);
        mp[si].push_back(i);
    }
    cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        int gc = root->getsum(l,r);
        //get cnt on this interval
        int ans = r-l+1;
        if (mp.count(gc)) {
            auto it1 = lower_bound(all(mp[gc]),l);
            auto it2 = upper_bound(all(mp[gc]),r);
            int d = distance(it1,it2);
            ans -= d;
        }
        cout << ans << '\n';
    }
}

