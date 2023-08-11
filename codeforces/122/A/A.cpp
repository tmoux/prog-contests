#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

bool isLucky(int n) {
    while (n) {
        int r = n % 10;
        if (r != 4 && r != 7) return false;
        n /= 10;
    }
    return true;
}

bool check(int n) {
    for (int i = 1; i*i <= n; i++) {
        if (n % i == 0) {
            if (isLucky(i) || isLucky(n/i)) return true;
        }
    }
    return false;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    cout << (check(n) ? "YES" : "NO") << '\n';

    return 0;
}
	

