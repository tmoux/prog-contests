#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5, maxk = 20;
int n, gcdT[maxn][maxk], minT[maxn][maxk];

int msb(int a) {
	return 31 - __builtin_clz(a);
}

int getgcd(int l, int r) {
	//queries [l,r)
	int ms = msb(r-l);
	return __gcd(gcdT[l][ms],gcdT[r-(1<<ms)][ms]);
}

int getmin(int l, int r) {
	int ms = msb(r-l);
	return min(minT[l][ms],minT[r-(1<<ms)][ms]);
}

bool isValid(int len) {
	for (int i = 0; i + len <= n; i++) {
		if (getgcd(i,i+len) == getmin(i,i+len)) return true;
	}
	return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    memset(gcdT,-1,sizeof(gcdT));
    memset(minT,-1,sizeof(minT));

    cin >> n;
    for (int i = 0; i < n; i++) {
    	cin >> gcdT[i][0];
    	minT[i][0] = gcdT[i][0];
    }

    for (int k = 1; k < maxk; k++) {
    	for (int i = 0; i < n; i++) {
   			int nx = i + (1 << (k-1));
   			if (nx > n) {
   				gcdT[i][k] = -1;
   				minT[i][k] = -1;
   			}
   			else {
   				gcdT[i][k] = __gcd(gcdT[i][k-1],gcdT[nx][k-1]);
   				minT[i][k] = min(minT[i][k-1],minT[nx][k-1]);
   			}
    	}
    }
  
  	int len = 0;
  	for (int k = maxk - 1; k >= 0; k--) {
  		int newlen = len + (1 << k);
  		if (isValid(newlen)) len = newlen;
  	}

  	//output
	vector<int> ans;
	for (int i = 0; i + len <= n; i++) {
		if (getgcd(i,i+len) == getmin(i,i+len)) {
			ans.push_back(i+1);
		}
	}  	
	cout << ans.size() << ' ' << len-1 << '\n';
	for (int i: ans) {
		cout << i << ' ';
	}


    return 0;
}