#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxm = 305;
int n, m;

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	int lazy;
	int mini;
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

	void add(int st, int en, int x) {
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

	int getmini(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return mini;
		}
		int ret = 1e9;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
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

typedef pair<int,int> pii;
pii interval[maxm];
int a[maxn];

inline bool contains(pii& a, int i) {
    return a.first <= i && i <= a.second;
}

pair<int,vector<int>> ans = {0,{}};
void update(int i, Node *seg) {
    vector<int> ret;
    ret.reserve(m);
    for (int j = 1; j <= m; j++) {
        if (!contains(interval[j],i)) {
            ret.push_back(j);
            seg->add(interval[j].first,interval[j].second,-1);            
        }
    }
    int mn = seg->getmini(1,n);
    if (ans.first < a[i]-mn) {
        ans = {a[i]-mn,ret};
    }
    for (int j: ret) {
        seg->add(interval[j].first,interval[j].second,1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    clock_t begin = clock();
    cin >> n >> m;
    Node *seg = new Node(1,n);
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        a[i] = ai;
        seg->add(i,i,ai);
    }
    for (int i = 1; i <= m; i++) {
        cin >> interval[i].first >> interval[i].second;
    }
    vector<int> perm;
    for (int i = 1; i <= n; i++) perm.push_back(i);
    sort(perm.begin(),perm.end(),[](int aa, int bb) { return a[aa] > a[bb]; });
    for (int q = 0; q < n && double(clock()-begin)/CLOCKS_PER_SEC < 1.8; q++) {
        int i = perm[q];
        update(i,seg);   
    }
    for (int q = n - 1; q >= 0 && double(clock()-begin)/CLOCKS_PER_SEC < 1.95; q--) {
        int i = perm[q];
        update(i,seg);
    }

    cout << ans.first << '\n';
    cout << ans.second.size() << '\n';
    for (int i: ans.second) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}
