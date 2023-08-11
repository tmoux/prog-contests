#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll maxi;
    ll mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		maxi = 0;
        mini = 0;
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


	void add(int i, ll x) {
		if (s == e) {
			sum += x;
			maxi = sum;
            mini = sum;
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
		maxi = max(l->maxi,r->maxi);
        mini = min(l->mini,r->mini);
	}

	ll getmaxi(int st, int en) {
		if (st <= s && e <= en) {
			return maxi;
		}
		ll ret = -1e18;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	

    ll getmini(int st, int en) {
		if (st <= s && e <= en) {
			return mini;
		}
		ll ret = 1e18;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}

	ll getsum(int st, int en) {
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

const int maxn = 1e5+5, INF = 1e9;
int N, S, L;
int a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> S >> L;
    Node *arr = new Node(1,N);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        arr->add(i,a[i]);
    }
    Node *dp = new Node(0,N);
    for (int i = 1; i < L; i++) {
        dp->add(i,INF);
    }
    for (int i = L; i <= N; i++) {
        int lo = 0, hi = i+1;
        while (lo + 1 < hi) {
            int mid = (lo+hi)>>1;
            int mx = arr->getmaxi(mid,i);
            int mn = arr->getmini(mid,i);
            if (mx-mn <= S) {
                hi = mid;
            }
            else {
                lo = mid;
            }
        }
        //cout << i << ": " << hi << '\n';
        int ans = hi-1 <= i-L ? dp->getmini(hi-1,i-L)+1 : INF;
        //cout << i << ": " << ans << '\n';
        dp->add(i,ans);
    }
    cout << (dp->getsum(N,N) > maxn ? -1 : dp->getsum(N,N)) << '\n';
}

