#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    int n, q; cin >> n >> q;
    cout << n << ' ' << q << '\n';
    while (q--) {
    	int t = rand() % 2 + 1;
    	int l = rand() % n + 1;
	    int r = rand() % n + 1;
	    if (l > r) swap(l,r);
    	if (t == 1) {	
	    	printf("%d %d %d\n",t,l,r);
	    }
	    else {
	    	int x = rand() % 1000000;
	    	printf("%d %d %d %d\n",t,l,r,x); //set [l,r] to x
	    }
    }


    return 0;
}