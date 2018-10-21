#include <iostream>
using namespace std;
typedef long long ll;
ll sum, x;

int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        ll ai; cin >> ai;
        sum += ai;
        x ^= ai;
    }
    cout << (sum - x) << '\n';
    return 0;
}
	

