#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, q;
bool lava[3][maxn];

struct QNode
{
    pair<int,int> a, b;
};

QNode merge(QNode x, QNode y) {
    if ((x.b.first == 0 && y.a.first == 0) || 
         x.b.second == 0 && y.a.second == 0) {
        return {x.a,y.b};
    }
    return {{1,1},{1,1}};
}

struct Node {
	int s, e, m;
	//covers s,e;
    QNode sum;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
        sum.a = {0,0}; 
        sum.b = {0,0}; 
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

	void add(int i, pair<int,int> x) {
		if (s == e) {
            sum.a = x;
            sum.b = x;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
        sum = merge(l->sum,r->sum);
	}

	QNode getsum(int st, int en) {
		if (st <= s && e <= en) {
			return sum;
		}
		QNode ret = {{0,0},{0,0}};
		if (st <= m) {
            ret = merge(ret,l->getsum(st,en));
		}
		if (en > m) {
            ret = merge(ret,r->getsum(st,en));
		}
		return ret;
	}
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    Node *root = new Node(1,n);
    while (q--) {
        int r, c; cin >> r >> c;
        lava[r][c] = !lava[r][c];
        root->add(c,{lava[1][c],lava[2][c]});
        auto q = root->getsum(1,n);
        /*
        for (int i = 1; i <= n; i++) {
            auto q = root->getsum(i,i);
            cout << q.a.first << ' ' << q.a.second << ' ' << q.b.first << ' ' << q.b.second << '\n';
        }
        cout << '\n';
        */
        if (q.a.first == 0 && q.b.second == 0) {
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
        }
    }
}

