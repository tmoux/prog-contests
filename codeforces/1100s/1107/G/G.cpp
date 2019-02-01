#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll lazy;
	ll maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = 0;
		maxi = 0;
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
		if (s != e) {
			l->lazy += lazy;
			l->sum += (l->e - l->s + 1) * lazy;
			l->maxi += lazy;

			r->lazy += lazy;
			r->sum += (r->e - r->s + 1) * lazy;
			r->maxi += lazy;
		}
		lazy = 0;
	}

	void add(int st, int en, int x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy += x;
			sum += (e - s + 1) * x;
			maxi += x;
			return;
		}
		push();
		if (st <= m) {
			l->add(st,en,x);
		}
		if (en > m) {
			r->add(st,en,x);
		}
		sum = l->sum + r->sum;
		maxi = max(l->maxi,r->maxi);
	}

	ll getmaxi(int st, int en) {
        if (st > en) return 0;
		push();
		//if completely included
		if (st <= s && e <= en) {
			return maxi;
		}
		ll ret = 0;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	

	ll getsum(int st, int en) {
        if (st > en) return 0;
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

const int maxn = 3e5+5;
int n, a;
int dist[maxn];
int c[maxn];
Node *val, *gaps;

ll sqr(int x) {
    return 1LL*x*x;
}

ll f(int l, int r) {
    if (l > r) return -(1LL<<62);
    if (l == r) return c[l];
    int m = (l+r)/2 + 1;
    int currgap = 0;
    int lgap = 0;
    int lp = m;
    ll maxlsum = 0;
    ll ans = 0;
    for (int rr = m; rr <= r; rr++) {
        ll rsum = val->getsum(m,rr);
        while (lp >= l && lgap <= currgap) {
            lgap = max(lgap,dist[lp]-dist[lp-1]);
            maxlsum = max(maxlsum,val->getsum(lp,m-1));        
            lp--;
        }
        ans = max(ans,maxlsum+rsum-sqr(currgap));                        
        //cout << rr << ": " << (maxlsum+rsum-sqr(currgap)) << '\n';
        //printf("lp = %d, maxlsum = %d, rsum = %d, currgap = %d\n",lp+1,maxlsum,rsum,currgap);
        currgap = max(currgap,dist[rr+1]-dist[rr]);
    }
    
    lgap = 0;
    maxlsum = 0;
    for (lp = m-1; lp >= l; lp--) {
        lgap = max(lgap,dist[lp+1]-dist[lp]);
        ll lsum = val->getsum(l,lp);
        maxlsum = max(maxlsum,lsum-sqr(lgap));
    }
    ll maxrsum = 0;
    for (int rr = m; rr <= r; rr++) {
        maxrsum = max(maxrsum,val->getsum(m,rr));
    }
    //ans = max(ans,maxrsum+maxlsum);
    //ans = max(ans,max(f(l,m-1),f(m+1,r)));

    return ans;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> a;
    gaps = new Node(1,n);
    val = new Node(1,n);
    for (int i = 1; i <= n; i++) {
        cin >> dist[i] >> c[i];
        c[i] = a - c[i];
    }
    for (int i = 1; i <= n; i++) {
        gaps->add(i,i,dist[i+1]-dist[i]);    
        val->add(i,i,c[i]);
    } //[l,r-1] for gaps segtree
    ll ans = f(1,n);
    cout << ans << '\n';            

    return 0;
}

