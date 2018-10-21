#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    bool A[10] = {1,0,0,0,0,0,0,0,0,0};
    int lo = 0, hi = 9;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (A[mid]) {
            lo = mid;
        }
        else hi = mid;
    }

    cout << lo << ' ' << hi << '\n';

    return 0;
}
	

