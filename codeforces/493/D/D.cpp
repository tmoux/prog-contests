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
    cout << (n % 2 ? "black" : "white") << '\n';
    if (n%2 == 0) {
        cout << "1 2\n";
    }

    return 0;
}
	

