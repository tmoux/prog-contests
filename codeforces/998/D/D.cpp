#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

ll ansSmall(int n) {
    set<int> s = {1,5,10,50};
    for (int i = 0; i < n - 1; i++) {
        set<int> ns;
        for (int j: s) {
            ns.insert(j+1);
            ns.insert(j+5);
            ns.insert(j+10);
            ns.insert(j+50);
        }
        s = ns;
    }
    return s.size();
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n; cin >> n;
    if (n <= 11) {
        cout << ansSmall(n) << '\n';
    }
    else {
        cout << (49*(n-11)+ansSmall(11)) << '\n';
    }



    return 0;
}
	

