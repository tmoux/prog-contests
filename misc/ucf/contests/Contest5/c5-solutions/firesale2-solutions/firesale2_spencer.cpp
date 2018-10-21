#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	int n, k;
	cin >> n >> k;
	ll a[n+1];
	a[0] = 0LL;
	for(int i = 1; i<=n; i++){
		cin >> a[i];
		a[i] = k - a[i];
		a[i] += a[i-1];
	}
	vector<pair<ll, int> > f;
	vector<pair<ll,  int> > l;
	f.push_back(make_pair(a[0],0));
	for(int i = 1; i<=n; i++){
		pair<ll, int> now = make_pair(a[i],i);
		if(now.first<f.back().first){
			f.push_back(now);
		}
	}
	l.push_back(make_pair(a[n],n));
	for(int i = n-1; i>=0; i--){
		pair<ll, int> now = make_pair(a[i],i);
		if(now.first>l.back().first){
			l.push_back(now);
		}
	}
	int ans = 0;
	int point = 0;
	for(int i = f.size()-1; i>=0; i--){
		while(point < l.size() && l[point].first < f[i].first){
			point++;
		}
		if(point==l.size()){
			break;
		}
		ans = max(ans,l[point].second - f[i].second);
	}
	cout << ans << endl;
}