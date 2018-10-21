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
    int a, b, c, d; cin >> a >> b >> c >> d;
    cout << ((abs(a-c) <= d || (abs(a-b) <= d && abs(b-c) <= d)) ? "Yes" : "No") << '\n';


    return 0;
}
	

