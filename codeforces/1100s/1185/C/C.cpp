#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, M;
int t[maxn];

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

int ord[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> M;
    vector<pair<int,int>> v;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        v.push_back({t[i],i});
    }
    sort(v.begin(),v.end());
    for (int i = 0; i < n; i++) {
        ord[v[i].second] = i+1;
    }
    Node *count = new Node(0,n);
    Node *sum = new Node(0,n);
        
    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            count->add(ord[i-1],1);
            sum->add(ord[i-1],t[i-1]);
        }
        int need = M - t[i];
        int lo = -1, hi = n+1;
        while (lo + 1 < hi) {
            int mid = (lo+hi)>>1;
            //cout << mid << endl;
            //assert(1 <= mid && mid <= n);
            int s = sum->getsum(0,mid);
            if (s <= need) {
                lo = mid;
            }
            else {
                hi = mid;
            }
        }
        //cout << i << ": " << lo << ' ' << count->getsum(0,lo) << '\n';
        int cnt = count->getsum(0,lo);
        //printf("%d, %d, %d\n",i,cnt,i-1-cnt);
        cout << (i-1-cnt) << ' ';
    }
    cout << '\n';
}

