#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int ans = 0;
    while (n--) {
        int a, b, c; cin >> a >> b >> c;
        if (a + b + c > 1) ans++;
    }
    cout << ans << '\n';

    return 0;
}
	

