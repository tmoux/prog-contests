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
			maxi = x;
            mini = x;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		maxi = max(l->maxi,r->maxi);
        mini = min(l->mini,r->mini);
	}

	ll getmaxi(int st, int en) {
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
};

class Prominence
{
public:
    long long sumOfProminences(int N, vector <int> coef, vector <int> idx, vector <int> val) {
        vector<ll> H;
        for (int i = 0; i < N; i++) {
            int parity = i % 2;
            ll a = coef[3*parity];
            ll b = coef[3*parity+1];
            ll c = coef[3*parity+2];
            H.push_back((((a*i+b) % 1000000007)*i + c) % 1000000007);
        }
        for (int j = 0; j < idx.size(); j++) {
            H[idx[j]] = val[j];
        }
        ll mx = 0;
        for (auto i: H) {
       		mx = max(mx,i);
        }
        vector<int> left(H.size()), right(H.size());
        for (int i = H.size()-1; i >= 0; i--) {
            right[i] = H[i];
            if (i < H.size()-1 && H[i] <= H[i+1]) 
                right[i] = max(right[i],right[i+1]);
        }
        for (int i = 0; i < H.size(); i++) {
            left[i] = H[i];
            if (i > 0 && H[i-1] <= H[i]) 
                left[i] = max(left[i],left[i-1]);
        }
        Node *seg = new Node(0,H.size()-1);
        for (int i = 0; i < H.size(); i++) {
            seg->add(i,H[i]);
        }
        ll ans = 0;
        for (int i = 0; i < H.size(); i++) {
            bool peak = true;
            if (i > 0 && H[i-1] >= H[i]) peak = false;
            if (i < H.size()-1 && H[i] <= H[i+1]) peak = false;
            if (peak) {
                if (H[i] == mx) {
                    ans += H[i];
                    continue;
                }
                ll lo = 0, hi = H[i];
                while (lo + 1 < hi) {
                    ll mid = (lo+hi)/2;
                    int l = i, r = i;
                    for (int k = 19; k >= 0; k--) {
                        int nr = r + (1<<k);
                        if (nr < H.size() && seg->getmini(i,nr) >= mid) {
                            r = nr;
                        }
                        int nl = l - (1<<k);
                        if (nl >= 0 && seg->getmini(nl,i) >= mid) {
                            l = nl;
                        }
                    }
                    if (seg->getmaxi(l,r) <= H[i]) {
                        hi = mid;
                    }
                    else lo = mid;
                }
                ans += H[i]-lo;
            } 
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    Prominence t;
}

