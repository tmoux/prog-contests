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
    int f, c, m;
    cin >> f >> c >> m;
    int ans = 0;
    for (int i = 0; i <= m / f; i++) {
        int over = m - i * f;
        if (over % c == 0) ans++;
    }
    cout << ans << '\n';


    return 0;
}
	

