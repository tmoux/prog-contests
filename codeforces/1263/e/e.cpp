#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+5000;
int n;
string s;

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	int lazy;
	int mini;
    int maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = 0;
		mini = 0;
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
			l->mini += lazy;
            l->maxi += lazy;

			r->lazy += lazy;
			r->sum += (r->e - r->s + 1) * lazy;
			r->mini += lazy;
            r->maxi += lazy;
		}
		lazy = 0;
	}

	void add(int st, int en, int x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy += x;
			sum += (e - s + 1) * x;
			mini += x;
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
		mini = min(l->mini,r->mini);
        maxi = max(l->maxi,r->maxi);
	}

	int getmini(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return mini;
		}
		int ret = 2e9+9;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}	

    int getmaxi(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return maxi;
		}
		int ret = -2e9;
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
};

char a[maxn];

int val(char c) {
    if (c == '(') return 1;
    else if (c == ')') return -1;
    else return 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    cin >> s;
    int pos = 0;
    Node *root = new Node(0,maxn);
    for (char c: s) {
        if (c == 'L') {
            pos--;
            pos = max(0,pos);
        }
        else if (c == 'R') {
            pos++;
        }
        else {
            int delta = val(c) - val(a[pos]);
            a[pos] = c;
            root->add(pos,maxn,delta);
        }
        //check if valid
        if (root->getsum(maxn,maxn) == 0 && root->getmini(0,maxn) == 0) {
            cout << root->getmaxi(0,maxn) << ' ';
        }
        else {
            cout << -1 << ' ';
        }
    }
    cout << '\n';
}

