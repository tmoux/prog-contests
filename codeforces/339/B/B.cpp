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
    int n, m; cin >> n >> m;    
    ll ans = 0;
    int pos = 1;
    for (int i = 0; i < m; i++) {
        int ai; cin >> ai;
        if (ai >= pos) {
            ans += (ai - pos);
        }
        else {
            ans += (n - abs(ai - pos));
        }
        pos = ai;
    }
    cout << ans << '\n';


    return 0;
}
	

