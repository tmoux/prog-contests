#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, l, r, Ql, Qr, w[maxn];

int calc(int ls, int rs) {
    if (ls >= rs) {
        int diff = ls - rs;
        return max(0,(diff-1)*Ql);
    }
    else {
        int diff = rs - ls;
        return max(0,(diff-1)*Qr);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> l >> r >> Ql >> Qr;
    for (int i = 0; i < n; i++) cin >> w[i];

    int cursum = 0;
    for (int i = 0; i < n; i++) cursum += l*w[i];
    int numLs = n, numRs = 0;
    int minans = cursum + calc(numLs,numRs);
    for (int i = n - 1; i >= 0; i--) {
        cursum += (r-l)*w[i];
        numLs--; numRs++;
        minans = min(minans,cursum + calc(numLs,numRs));
        //cout << i << ' ' << cursum << ' ' << calc(numLs,numRs) << '\n';
    }

    cout << minans << '\n';

    return 0;
}
	

