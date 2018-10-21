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
    int a, b; cin >> a >> b;
    int ans = (b >= a) ? a : a-1;
    cout << ans << '\n';


    return 0;
}
	

