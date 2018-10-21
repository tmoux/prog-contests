#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n, k;
void subtract(int& n) {
    if (n % 10 != 0) n--;
    else n /= 10;
}
int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        subtract(n);
    }
    cout << n << '\n';


    return 0;
}
	

