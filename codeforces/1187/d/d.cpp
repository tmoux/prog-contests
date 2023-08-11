#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, a[maxn], b[maxn];
int pos[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll lazy;
	ll mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = 0;
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

	void push() {
		if (s != e) {
			l->lazy += lazy;
			l->sum += (l->e - l->s + 1) * lazy;
			l->mini += lazy;

			r->lazy += lazy;
			r->sum += (r->e - r->s + 1) * lazy;
			r->mini += lazy;
		}
		lazy = 0;
	}

	void add(int st, int en, ll x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy += x;
			sum += (e - s + 1) * x;
			mini += x;
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
		mini = min(l->mini,r->mini);
	}

	ll getmini(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return mini;
		}
		ll ret = 1000000000000000000;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
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

void solve(map<int,int>& mp) {
    for (auto p: mp) {
        if (p.second != 0) {
            cout << "NO\n";
            return;
        }
    }
    //cout << "OK" << endl;
    map<int,vector<int>> mpp;
    Node *root = new Node(1,n);
    for (int i = 1; i <= n; i++) {
        mpp[a[i]].push_back(i);
        root->add(i,i,a[i]);
    }
    for (int i = n; i >= 1; i--) {
        pos[i] = mpp[b[i]].back();
        mpp[b[i]].pop_back();
        //cout << i << ": " << pos[i] << '\n';
    }
    for (int i = 1; i <= n; i++) {
        int p = pos[i];
        //cout << i << ' ' << pos[i] << ": " << root->getmini(1,p) << '\n';
        if (root->getmini(1,p) < b[i]) {
            //impossible
            cout << "NO\n";
            return;
        }
        else {
            root->add(p,p,n+1);
        }
    }
    cout << "YES\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        map<int,int> mp;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            mp[a[i]]++;
        }
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            mp[b[i]]--;
        }
        solve(mp);
    }

}

