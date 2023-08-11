#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	int lazy;
	int maxi;
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

	int getmaxi(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return maxi;
		}
		int ret = -1e9;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	

	int getsum(int st, int en) {
		push();
		//if completely included
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

    int walk() {
        if (s == e) return s;
        push();
        if (r->maxi > 0) return r->walk();
        return l->walk();
    }
};

const int maxn = 1e5+5;
int m;

int val[maxn];

set<pair<int,int>> s;
vector<pair<int,int>> st;
void compute() {
    st.clear();
    for (auto p: s) {
        if (p.second == 0) {
            if (!st.empty()) st.pop_back();
        }
        else {
            st.push_back(p);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> m;
    Node *root = new Node(1,m);
    for (int qq = 0; qq < m; qq++) {
        int t, p; cin >> p >> t;
        if (t == 0) {
            root->add(1,p,-1);
        }
        else {
            int vi; cin >> vi;
            val[p] = vi;
            root->add(1,p,1);
        }
        if (root->getmaxi(1,m) < 1)
            cout << -1 << '\n';
        else {
            cout << val[root->walk()] << '\n';
        }
        /*
        bool found = false;
        for (int i = m; i >= 1; i--) {
            if (root->getmaxi(i,i) > 0) {
                cout << val[i] << '\n';
                found = true;
                break;
            }
        }
        if (!found) {
            cout << -1 << '\n';
        }
        */
    }    
}

