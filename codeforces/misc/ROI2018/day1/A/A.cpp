#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
	int s, e, m;
	//covers s,e;
    int maxi;
    int pos; //position of max element
	Node *l, *r;

	Node(int a, int b) {
		s = a;
		e = b;
		maxi = 0;
        pos = 0;
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

	void add(int i, int x) {
		if (s == e) {
			maxi = max(maxi,x);
            pos = s;    
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
        if (l->maxi > r->maxi) pos = l->pos;
        else pos = r->pos;
	}

	pair<int,int> getmaxi(int st, int en) {
		if (st <= s && e <= en) {
			return {maxi,pos};
		}
		pair<int,int> ret = {-1,-1};
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}
};

int n, m, q;
vector<Node*> rows, cols;
vector<vector<int>> grid;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> q;
    for (int i = 0; i <= n; i++) {
        rows.push_back(new Node(1,m));
        grid.push_back(vector<int>(m+1));
    }
    for (int i = 0; i <= m; i++) {
        cols.push_back(new Node(1,n));
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int ai; cin >> ai;
            grid[i][j] = ai;
            rows[i]->add(j,ai);
            cols[j]->add(i,ai);
        }
    }
    int curr = 0;
    for (int i = 1; i <= n; i++) {
        pair<int,int> p = rows[i]->getmaxi(1,m);
        if (cols[p.second]->getmaxi(1,n).second == i) {
            curr++;
            //cout << i << ' ' << p.second << ": " << grid[i][p.second] << '\n';
        }
    }
    while (q--) {
        int i, j, ai; cin >> i >> j >> ai;
            
    }
}

