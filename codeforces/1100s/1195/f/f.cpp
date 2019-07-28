#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, q;

vector<int> pts[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
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
			sum += x;
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
	}

	int getsum(int st, int en) {
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

pair<int,int> reduce(pair<int,int> a, pair<int,int> b) {
    int x = b.first - a.first;
    int y = b.second - a.second;
    if (x == 0) return {0,y<0?-1:1};
    if (y == 0) return {x<0?-1:1,0};
    int gc = abs(__gcd(x,y));
    x /= gc;
    y /= gc;
    return {x,y}; 
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    map<pair<int,int>,int> mp;
    int curr = 0;
    for (int j = 1; j <= n; j++) {
        int k; cin >> k;
        vector<pair<int,int>> v;
        for (int a = 0; a < k; a++) {
            int x, y; cin >> x >> y;
            v.push_back({x,y});
        }
        v.push_back(v[0]);
        for (int i = 0; i < k; i++) {
            pair<int,int> p = reduce(v[i],v[i+1]);            
            //cout << p.first << ' ' << p.second << '\n';
            if (mp.count(p)) pts[j].push_back(mp[p]);
            else {
                pts[j].push_back(mp[p] = curr++);
            }
        }
        //cout << "\n";
    }
    cin >> q;
    vector<pair<pair<int,int>,int>> qs;
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        qs.push_back({{l,r},i});
    }
    sort(qs.begin(),qs.end(),[](auto a, auto b) {
            return a.first.second < b.first.second;
            });
    vector<int> ans(q);
    vector<int> lastSeen(curr+1,-1);
    Node *root = new Node(1,n);
    int pt = 1;
    for (auto query: qs) {
        int l = query.first.first;
        int r = query.first.second;
        int id = query.second;
        
        //update right side
        while (pt <= r) {
            for (int i: pts[pt]) {
                root->add(pt,1);
                if (lastSeen[i] != -1) {
                    root->add(lastSeen[i],-1);
                }
                lastSeen[i] = pt;
            }
            pt++;
        }
        ans[id] = root->getsum(l,r);
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}

