#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1000005;
int n, A[10];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int mincost = maxn, idx;
    for (int i = 1; i <= 9; i++) {
        cin >> A[i];
        if (A[i] <= mincost) {
            idx = i;
            mincost = A[i];
        }
    }
    int len = n / mincost;
    if (len == 0) {
        cout << -1 << '\n';
        return 0;
    }
    n -= len*mincost;
    string res(len,idx+'0');
    for (int i = 0; i < len; i++) {
        for (int bet = 9; bet > idx; bet--) {
            if (n - A[bet] + mincost >= 0) {
                n = n - A[bet] + mincost;
                res[i] = bet + '0';
                break;
            }
        }
    }
    cout << res << '\n';


    return 0;
}
	

