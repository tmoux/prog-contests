#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
#define all(v) v.begin(), v.end()
const int maxn = 200005;
const int INF = 2000000000;
vector<ll> tree[4*maxn];
int n;
ll t;
ll arr[maxn];

void build(int node, int l, int r) {
	if (l == r) {
		tree[node] = {arr[l]};
		return;
	}
	int mid = (l+r) >> 1;
	int left = node << 1, right = (node<<1)|1;
	
	build(left,l,mid);
	build(right,mid+1,r);
	merge(all(tree[left]),all(tree[right]),back_inserter(tree[node]));
	/*
	if (l == 1 && r == n) {
        cout << l << ' ' << r << "\n";
        for (ll i: tree[node]) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    */
}

ll query(int node, int l, int r, int i, int j, ll k) {
	if (i > r || j < l) return 0LL;
	if (i <= l && r <= j) {
		/*
		cout << k << '\n';	
		cout << l << ' ' << r << '\n';
		for (ll a: tree[node]) {
			cout << a << ' ';
		}
		cout << '\n';
		*/
		return (ll)(lower_bound(all(tree[node]),k) - tree[node].begin());
	}
	int mid = (l+r) >> 1;
	int left = node << 1, right = (node<<1)|1;
	return query(left,l,mid,i,j,k) + query(right,mid+1,r,i,j,k);
}

int queryWrap(int i, int j, ll k) {
	return query(1,1,n,i,j,k);
}


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> t;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		arr[i] += arr[i-1];
	}
	build(1,1,n);
	
	ll ans = 0LL;
	for (int i = 1; i <= n; i++) {
		ll r = queryWrap(i,n,arr[i-1]+t-1);
		/*if (i == 44) {
			cout << i << " " << arr[i-1]+t << '\n';
			cout << (arr[i]-1 +t < arr[44]) << '\n';
		}*/
		
		ans += r;
	}
	cout << ans << '\n';
	
	
	return 0;
}
