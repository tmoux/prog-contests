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
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    int x, y; cin >> x >> y;
    int ax = abs(x1-x2), ay = abs(y1-y2);
    if (ax % x != 0 || ay % y != 0) {
        cout << "NO\n";
        return 0;
    }
    cout << (((ax/x) & 1) ^ ((ay/y) & 1) ? "NO" : "YES") << '\n';


    return 0;
}
	

