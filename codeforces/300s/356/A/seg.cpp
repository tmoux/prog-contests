#include <iostream>
#include <map>
#include <queue>
using namespace std;

const int maxn = 3e5+5;
int seg[3*maxn], s[3*maxn], e[3*maxn];

void build(int i, int l, int r) {
	s[i] = l;
	e[i] = r;
	seg[i] = 0;
	int mid = (l+r)/2;
	if (l != r) {
		build(i*2,l,mid);
		build(i*2+1,mid+1,r);
	}
}

void add(int i, int ind, int x) {
    //cout << i << ' ' << ind << ' ' << x << '\n';
	if (s[i] == e[i]) {
		seg[i] = x;
        return;
	}
	int m = (s[i]+e[i])/2;
	if (ind <= m) add(i*2,ind,x);
	else add(i*2+1,ind,x);
	seg[i] = gcd(seg[i*2],seg[i*2+1]);
}

int q;

int main() {
	#ifdef OFFLINE
	freopen("in","r",stdin);
	#endif
    ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> q;
	build(1,0,q);
	map<int,queue<int>> mp;
	for (int i = 0; i < q; i++) {
		char c; int x; cin >> c >> x;
		if (c == '+') {
			mp[x].push(i);
			add(1,i,x);
		}
		else {
			int j = mp[x].front();
			mp[x].pop();
			add(1,j,0);
		}
		int ans = seg[1];
		cout << (ans == 0 ? 1 : ans) << '\n';
	}
}
