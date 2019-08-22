#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct QQ
{
    int n0, n1, n01;
    QQ(int _n0, int _n1, int _n01) {
        n0 = _n0;
        n1 = _n1;
        n01 = _n01;
    }
};

QQ comb(QQ a, QQ b) {
    //QQ ret = QQ(a.n0+b.n0,a.n1+b.n1,max(a.n01+b.n1,max(a.n0+b.n01,a.n0+b.n1)));
    QQ ret = QQ(a.n0+b.n0,a.n1+b.n1,max(a.n01+b.n1,a.n0+b.n01));
    return ret;
}

bool flag = true;

struct Node {
	int s, e, m;
	//covers s,e;
    int n0, n1, n01;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
        n0 = n1 = n01 = 0;
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

    void pull() {
        n0 = l->n0 + r->n0;
        n1 = l->n1 + r->n1;
        n01 = max(l->n01 + r->n1,l->n0 + r->n01);
    }

	void add(int i, int x) {
		if (s == e) {
            if (x == 0) {
                n0 = 1;
                n1 = 0;
                n01 = 1;
            }
            else {
                n0 = 0;
                n1 = 1;
                n01 = 1;
            }
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
        
        int old = n01;
        pull();
        if (old != n01) {
            flag = false;
        }
	}

	QQ getsum(int st, int en) {
		if (st <= s && e <= en) {
			return QQ(n0,n1,n01);
		}
		QQ ret = QQ(0,0,0);
		if (st <= m) {
            ret = comb(ret,l->getsum(st,en));
		}
		if (en > m) {
            ret = comb(ret,r->getsum(st,en));
		}
		return ret;
	}
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int n = s.size();
    Node *root = new Node(0,n-1);
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            root->add(i,0);
        }
        else {
            root->add(i,1);
        }
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') continue;
        flag = true;
        root->add(i,0);
        if (flag) {
            s[i] = '0';
        }
        else {
            root->add(i,1);
        }
    }
    cout << s << '\n';
}

