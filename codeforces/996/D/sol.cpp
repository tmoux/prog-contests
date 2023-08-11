#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, A[maxn*2];

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
	#endif
	
	cin >> n;
	for (int i = 0; i < 2*n; i++) {
		cin >> A[i];
	}

	int seen[2*maxn];
	int ans = 0;
	while (true) {
        /*
        for (int i = 0; i < 2*n; i++) {
            cout << A[i] << ' ';
        }
        cout << '\n';
        */
		memset(seen,0,sizeof(seen));
        bool flag = true;
		for (int i = 0; i < 2*n; i++) {
			seen[A[i]]++;
			if (seen[A[i]] == 2) {
				if (A[i-1] != A[i]) {
					//needs to be swapped
					swap(A[i],A[i-1]);
					ans++;
                    flag = false;
					break;
				}
			}
		}
        if (flag) {
            break;
        }
	}
	cout << ans << '\n';

	
	return 0;
}
