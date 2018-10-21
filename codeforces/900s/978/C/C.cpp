#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
ll A[maxn];
int n, m;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    ll curr = A[1];
    ll prev = 0;
    int idx = 1;
    for (int i = 0; i < m; i++) {
        ll bi; cin >> bi;
        while (curr < bi) {
            prev = curr;
            curr += A[++idx];
        }
        int f = idx;
        ll k = bi - prev;
        cout << f << ' ' << k << '\n';
    }


    return 0;
}
	

