#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+6;
const ll INF = 1e18;
int n, k;

class Node {
public:
	int s, e, m;
	//coverse s,e;
	ll sum;
	ll mini;
	Node *l, *r;

	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
        mini = INF;
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

	void add(int ind, ll x) {
		sum += x;
		if (s == e) {
			mini = sum;
			return;
		}
		int m = (s+e)/2;
		if (ind <= m) {
			l->add(ind,x);
		}
		else {
			r->add(ind,x);
		}
		mini = min(l->mini,r->mini);
	}

	ll getsum(int st, int en) {
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

	ll getmini(int st, int en) {
		//if completely included
		if (st <= s && e <= en) {
			return mini;
		}
		ll ret = INF;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}

    int getR(ll k) {
        //returns rightmost index of number m s.t. m <= k
        if (s == e) return s;

        if (r->mini <= k) return r->getR(k);
        else if (l->mini <= k) return l->getR(k);
        else return -1; //just in case it's invalid
    }
};


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //input
    cin >> n >> k;
    Node* root = new Node(0,n);
    ll prev = 0;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        root->add(i,ai-k+prev);
        prev += ai-k;
    }

    //calculate answer
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int r = root->getR(root->getsum(i-1,i-1));       
        ans = max(ans,(r-i+1));
        //cout << i << ' ' << r << '\n';
    }
    cout << ans << '\n';

    return 0;
}


	

