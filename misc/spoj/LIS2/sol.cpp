#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N;

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll maxi;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
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


	void add(int i, ll x) {
		if (s == e) {
            sum = max(sum,x);
			maxi = sum;
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
	}

	ll getmaxi(int st, int en) {
		if (st <= s && e <= en) {
			return maxi;
		}
		ll ret = 0;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	

	ll getsum(int st, int en) {
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

int dp[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    vector<pair<int,int>> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(),a.end());
    map<int,int> x;
    int pt = 1;
    for (auto& p: a) {
        if (x.count(p.first)) p.first = x[p.first];
        else p.first = x[p.first] = pt++;
    }
    sort(a.begin(),a.end(),[](auto a, auto b) {
            return a.second < b.second;
            });
    map<int,int> y;
    pt = 1;
    for (auto& p: a) {
        if (y.count(p.second)) p.second = y[p.second];
        else p.second = y[p.second] = pt++;
    }
    sort(a.begin(),a.end());
    Node *root = new Node(0,N);
    vector<vector<pair<int,int>>> batches;
    vector<pair<int,int>> curr;
    int prevx = -1;
    for (auto p: a) {
        if (p.first != prevx) {
            if (prevx != -1) {
                batches.push_back(curr);
            }
            curr.clear();
            prevx = p.first;
        }
        curr.push_back(p);
    }
    int ans = 0;
    batches.push_back(curr);
    for (vector<pair<int,int>>& batch: batches) {
        vector<pair<int,int>> adds;
        for (auto p: batch) {
            int mx = root->getmaxi(0,p.second-1) + 1;
            cout << p.first << ' ' << p.second << ": " << mx << '\n';
            adds.push_back({p.second,mx});    
            ans = max(ans,mx);
        }
        for (auto p: adds) {
            root->add(p.first,p.second);
        }
        cout << '\n';
    }
    cout << ans << '\n';
}

