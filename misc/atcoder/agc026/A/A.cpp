#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, A[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        if (i > 0) {
            if (A[i] == A[i-1]) {
                A[i] = -1;
                ans++;
            }
        }
    }
    cout << ans << '\n';

    return 0;
}
	

