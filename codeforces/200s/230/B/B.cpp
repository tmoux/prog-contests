#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

bool isPrime(int n) {
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        ll a; cin >> a;
        if (a != 1 && (ll)(sqrt(a))*(ll)(sqrt(a)) == a && isPrime((int)(sqrt(a)))) {
            cout << "YES" << '\n';
        }
        else {
            cout << "NO" << '\n';
        }
    }


    return 0;
}
	

