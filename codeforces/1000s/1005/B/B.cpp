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
    string s, t; cin >> s >> t;
    int t1 = s.size() - 1, t2 = t.size() - 1;
    while (t1 >= 0 && t2 >= 0 && s[t1] == t[t2]) {
        t1--;
        t2--;
    }
    int ans = t1 + 1 + t2 + 1;
    cout << ans << '\n';


    return 0;
}
	

