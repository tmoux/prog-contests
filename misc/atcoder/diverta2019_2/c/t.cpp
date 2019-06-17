#include <bits/stdc++.h>
 
#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb(x) push_back(x)
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
const int MX = 100005;
int n, a[MX], s = 0, p = 0;
vii res;
 
int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] < 0) p++;
	}
	sort(a, a+n);
 
	p = max(1, p);
	p = min(n - 1, p);
 
	if (p == n - 1) {
		s = a[n - 1];
		for (int i = 0; i < n - 1; i++) {
			res.emplace_back(s, a[i]);
			s -= a[i];
		}
	} else {
		res.emplace_back(a[p-1], a[p]);
		s = a[p-1] - a[p];
		for (int i = p + 1; i < n - 1; i++) {
			res.emplace_back(s, a[i]);
			s -= a[i];
		}
		res.emplace_back(a[n-1], s);
		s = a[n-1] - s;
		for (int i = 0; i < p - 1; i++) {
			res.emplace_back(s, a[i]);
			s -= a[i];
		}
	}
 
	cout << s << endl;
	for (ii &r : res)
		cout << r.fi << " " << r.se << endl;
 
	return 0;
}
