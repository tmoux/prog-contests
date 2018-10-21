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
    int prev = -1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int d; cin >> d;
        if (d != prev) {
            ans++;
        }
        prev = d;
    }
    cout << ans << '\n';


    return 0;
}
	

