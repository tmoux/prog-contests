#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int N[maxn], n;
ll f[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int mx = -1;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        N[ai]++;
        mx = max(mx,ai);
    }
    f[mx] = mx*N[mx];
    for (int i = mx-1; i >= 0; i--) {
        f[i] = max(i*N[i] + f[i+2],(i+1)*N[i+1] + f[i+3]);
    }
    cout << f[1] << '\n';
   


    return 0;
}
	

