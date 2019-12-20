#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n;
string s;
int pre[2*maxn];

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

struct Bracket
{
    int start, end;
    vector<pair<int,pair<int,int>>> vs;
};

int cv(int i) {
    return ((i-1) % n) + 1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
    s += s;
    Node *root = new Node(1,2*n);
    for (int i = 0; i < s.size(); i++) {
        pre[i+1] = pre[i];
        if (s[i] == '(') pre[i+1]++;
        else pre[i+1]--;
        root->add(i+1,i+1,pre[i+1]);
    }
    if (pre[n] != 0) {
        //none possible
        cout << 0 << '\n';
        cout << 1 << ' ' << 1 << '\n';
        return 0;
    }
    int pos = -1;
    for (int i = 1; i <= n; i++) {
        //cout << root->getmini(i,i) << '\n';
        //cout << root->getmini(i,i+n-1) << '\n';
        if (root->getmini(i,i+n-1) == pre[i-1]) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        assert(false);
        cout << "0\n1 1\n";
        return 0;
    }
    int d0 = pre[pos-1];
    int d1 = d0 + 1;
    int d2 = d1 + 1;
    vector<Bracket> ans;
    Bracket b;
    b.start = pos;
    vector<pair<int,pair<int,int>>> currs; //num, [start,end]
    pair<int,pair<int,int>> c;
    for (int i = pos; i < pos+n; i++) {
        if (pre[i] == d0) {
            b.end = i;
            b.vs = currs;
            currs.clear();
            ans.push_back(b);
            b.start = i+1;
        }
        else {
            if (s[i-1] == '(' && pre[i] == d1+1) {
                c.second.first = i;
                c.first = 0;
            }
            if (s[i-1] == ')' && pre[i] == d1) {
                c.second.second = i;
                currs.push_back(c);
                c = {0,{0,0}};
            }
            else if (s[i-1] == ')' && pre[i] == d2) {
                c.first++;
            }
        }
    }
    int res = 0;
    pair<int,int> ret = {1,1};
    for (auto v: ans) {
        int r = (int)v.vs.size()-(int)ans.size()+1;
        if (r > res) {
            res = r;
            ret = {cv(v.start),cv(v.end)};
        }
        for (auto p: v.vs) {
            if (p.first+1 > res) {
                res = p.first+1;
                ret = {cv(p.second.first),cv(p.second.second)};
            }
            //printf("num = %d, [%d,%d]\n",p.first,p.second.first,p.second.second);
        }
    }
    cout << (res+ans.size()) << '\n';
    cout << ret.first << ' ' << ret.second << '\n';
}

