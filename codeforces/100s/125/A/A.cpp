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
    if ((n+1) % 36 == 0) n++;
    int ft = n/36;
    n %= 36;
    int in;
    if (n % 3 == 0 || (n-1) % 3 == 0) in = n/3;
    else in = n/3 + 1;
    cout << ft << ' ' << in << '\n';


    return 0;
}
	

