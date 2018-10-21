#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int sumDigits(int n) {
    int res = 0;
    while (n) {
        res += n % 10;
        n /= 10;
    }
    return res;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x = 29;
    while (!(sumDigits(x) == 29 && x % 100 == 29)) {
        x += 29;
    }
    cout << x << '\n';


    return 0;
}
	

