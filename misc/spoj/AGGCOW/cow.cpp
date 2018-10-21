#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, c, A[maxn];

bool check(int x) {
	int cows = 0, prev = -1e9-9;
	for (int i = 0; i < n; i++) {
		if (prev + x <= A[i]) {
			prev = A[i];
			cows++;
		}
	}
	return cows >= c;
}

int main()
{
    int t; cin >> t;
    while (t--) {
    	cin >> n >> c;
    	for (int i = 0; i < n; i++) cin >> A[i];
    	sort(A,A+n);
    	int lo = 0, hi = 1e9+5;
    	while (lo + 1 < hi) {
    		int mid = (lo+hi)/2;
    		bool ch = check(mid);
    		if (ch) {
    			lo = mid;
    		}
    		else {
    			hi = mid;
    		}
    	}
    	cout << lo << '\n';
    }

    return 0;
}