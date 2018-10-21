#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ull MOD = 1e9+7;
map<ull,ull> F;

ull f(ull n) {
    if (F.count(n)) return F[n];
    ull k = n/2;
    if (n % 2 == 0) {
        return F[n] = (f(k)*f(k) + f(k-1)*f(k-1)) % MOD;
    }
    else {
        return F[n] = (f(k)*f(k+1) + f(k-1)*f(k)) % MOD;
    }
}


int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    


    return 0;
}
	

