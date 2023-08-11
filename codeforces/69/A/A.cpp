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
    int x = 0, y = 0, z = 0;
    for (int i = 0; i < n; i++) {
        int xx, yy, zz; cin >> xx >> yy >> zz;
        x += xx;
        y += yy;
        z += zz;
    }
    cout << (!x && !y && !z ? "YES" : "NO") << '\n';


    return 0;
}
	

