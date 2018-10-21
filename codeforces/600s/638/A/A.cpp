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
    int n, a; cin >> n >> a;
    if (a % 2 == 1) {
        cout << (a+1)/2 << '\n';
    }
    else {
        cout << (n-a)/2+1 << '\n';
    }


    return 0;
}
	

