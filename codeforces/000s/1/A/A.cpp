#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

template<typename T>
T ceildiv(T a, T b) {
    return (a % b == 0 ? a/b : a/b+1);
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, m, a; cin >> n >> m >> a;
    cout << (ceildiv(n,a)*ceildiv(m,a)) << '\n';


    return 0;
}
	

