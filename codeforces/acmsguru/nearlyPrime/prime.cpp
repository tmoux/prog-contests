#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

bool nearlyPrime(int pi) {
    int numFactors = 1;
    for (int i = 2; i*i <= pi; i++) {
        if (numFactors == 1 && i*i == pi) {
            return true;
        }
        while (pi % i == 0) {
            numFactors++;
            pi /= i;
        }
    }

    return numFactors == 2;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("input.in","r",stdin);
    int n; cin >> n;
    while (n--) {
        int pi; cin >> pi;
        cout << ((nearlyPrime(pi)) ? "Yes" : "No") << '\n';
    }


    return 0;
}
	

