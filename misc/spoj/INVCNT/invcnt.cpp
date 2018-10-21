#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e6+5;
int bit[maxn], A[maxn];
int sum(int i) {
	int res = 0;
	while (i) {
		res += bit[i];
		i -= i & (-i);
	}
	return res;
}
void add(int i, int x) {
	while (i < maxn) {
		bit[i] += x;
		i += i & (-i);
	}
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    int t; cin >> t;
    while (t--) {
    	memset(bit,0,sizeof bit);
    	memset(A,0,sizeof A);
    	int n; cin >> n;
    	vector<pair<int,int>> a(n);
    	for (int i = 0; i < n; i++) {
    		cin >> a[i].first;
    		a[i].second = i;
    	}
    	sort(a.begin(),a.end());
    	for (int i = 0; i < n; i++) {
    		A[a[i].second] = i+1;
    	}
    	ll inv = 0;
    	for (int i = n - 1; i >= 0; i--) {
    		inv += sum(A[i]-1);
    		add(A[i],1);
    	}
    	cout << inv << '\n';
    }


    return 0;
}