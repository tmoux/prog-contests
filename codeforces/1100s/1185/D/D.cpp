#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn];

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

int ord[maxn];

bool good(vector<int> b) {
    for (int i = 1; i < b.size() - 1; i++) {
        if (b[i+1]-b[i] != b[i]-b[i-1]) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    vector<pair<int,int>> pp;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pp.push_back({a[i],i});
    }
    sort(pp.begin(),pp.end());
    for (int i = 0; i < pp.size(); i++) {
        ord[i+1] = pp[i].second;
    }
    sort(a+1,a+1+n);

    if (n <= 100) {
        for (int i = 1; i <= n; i++) {
            vector<int> b;
            for (int j = 1; j <= n; j++) {
                if (j != i) b.push_back(a[j]);
            }
            if (good(b)) {
                cout << ord[i] << '\n';
                return 0;
            }
        }
        cout << -1 << '\n';
        return 0;
    }

    Node *diffs = new Node(1,n-1);
    for (int i = 1; i < n; i++) {
        diffs->add(i,a[i+1]-a[i]);
    }
    for (int i = 1; i <= n; i++) {
        //try to delete it
        if (i == 1) {
            if (diffs->getmini(2,n-1) == diffs->getmaxi(2,n-1)) {
                cout << ord[i] << '\n';
                return 0;
            }
        }
        else if (i == 2) {
            if (diffs->getmini(3,n-1) == diffs->getmaxi(3,n-1) && diffs->getmaxi(3,n-1) == a[i+1]-a[i-1]) {
                cout << ord[i] << '\n';
                return 0;
            }
        }
        else if (i == n-1) {
            if (diffs->getmini(1,n-3) == diffs->getmaxi(1,n-3) && diffs->getmaxi(1,n-3) == a[i+1]-a[i-1]) {
                cout << ord[i] << '\n';
                return 0;
            }
        }
        else if (i == n) {
            if (diffs->getmini(1,n-2) == diffs->getmaxi(1,n-2)) {
                cout << ord[i] << '\n';
                return 0;
            }
        }
        else {
            if (min(diffs->getmini(1,i-2),diffs->getmini(i+1,n-1)) == max(diffs->getmaxi(1,i-2),diffs->getmaxi(i+1,n-1)) && max(diffs->getmaxi(1,i-2),diffs->getmaxi(i+1,n-1)) == a[i+1]-a[i-1]) {
                cout << ord[i] << '\n';
                return 0;
            }
        }
    }
    cout << -1 << '\n';
}

