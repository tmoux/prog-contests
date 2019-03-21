#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
const ll INV = -(1LL<<62);
int n, q;
ll a[maxn], k[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll lazy;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = INV;
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

	void push() {
		if (lazy == INV) return;
		if (s != e) {
			l->lazy = lazy;
			l->sum = (l->e - l->s + 1) * lazy;

			r->lazy = lazy;
			r->sum = (r->e - r->s + 1) * lazy;
		}
		lazy = INV;
	}

	void pull() {
		sum = l->sum + r->sum;
	}

	void add(int st, int en, ll x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy = x;
			sum = (e - s + 1) * x;
			return;
		}
		push();
		if (st <= m) {
			l->add(st,en,x);
		}
		if (en > m) {
			r->add(st,en,x);
		}
		pull();
	}

	ll getsum(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return sum;
		}
		ll ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};

struct SQT
{
    int sz;
    int n;
    vector<int> arr;
    vector<vector<int>> blocks;
    vector<int> sum;
    vector<int> bucket;
    vector<int> largest; //idx of largest # in bucket
    SQT(int _n) {
        arr.resize(maxn);
        blocks.resize(maxn);
        sum.resize(maxn);
        largest.resize(maxn);
        n = _n;
        sz = sqrt(n) + 1;
        bucket = vector<int>(sz+10,-1);
        for (int i = 1; i <= n; i++) {
            bucket[i] = (i-1)/sz;
            blocks[bucket[i]].push_back(a[i]);    
            arr[i] = a[i];
        }
        for (int i = 1; i <= n; i++) {
            if (bucket[i] != bucket[i+1]) largest[bucket[i]] = i;
        }
    }

    ll getsum(int l, int r) {
        ll res = 0;
        while (l != 1 && bucket[l] == bucket[l-1]) {
            res += arr[l];
            l++;
        }
        while (bucket[l] != bucket[r]) {
            res += sum[bucket[l]];
            l += sz;
        }
        for (; l <= r; l++) {
            res += arr[l];
        }
        return res;
    }

    void add(int i, int x) {
                    
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    Node *root = new Node(1,n+1);
    for (int i = 1; i <= n; i++) {
        root->add(i,i,a[i]);
    }
    cin >> q;
    while (q--) {
        char c; cin >> c;
        if (c == 's') {
            int l, r; cin >> l >> r;
            ll ans = root->getsum(l,r);
            cout << ans << '\n';
        }
        else {
            int i, x; cin >> i >> x;
            ll ai = root->getsum(i,i);
            //root->add(i,n,ai+x); //make ai+x the max of invl [i,n]
            int lo = i, hi = n+1;
            while (lo + 1 < hi) {
                int m = (lo+hi)/2;
                if (root->getsum(m,m) <= ai + x) lo = m;
                else hi = m;
            }
            assert(i <= lo && root->getsum(lo,lo) <= ai + x);
            //root->add(i,lo,ai+x);
            for (int j = i; j <= n; j++) {
                root->add(j,j,max(ai+x,root->getsum(j,j)));
            }
        }
    }
}

