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
    ll n, m, a, b;
    cin >> n >> m >> a >> b;
    ll d1 = n/m*m, d2 = d1+m;
    ll cost1 = (n-d1)*(b);
    ll cost2 = (d2-n)*(a);
    cout << min(cost1,cost2) << '\n';


    return 0;
}
	

