#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

ll a, b;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> a >> b;
    vector<ll> vec;
    while (b >= a) {
        vec.push_back(b);
        if (b == a) {
            cout << "YES" << '\n';
            cout << vec.size() << '\n';
            for (int i = vec.size() - 1; i >= 0; i--) {
                cout << vec[i] << ' ';
            }
            return 0;
        }
        if (b % 10 == 1) {
            b /= 10;
        }
        else if (b % 2 == 0) {
            b /= 2;
        }
        else {
            break;
        }
    }
    cout << "NO\n";

   
    return 0;
}
	

