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
    ll n, m, k;
    cin >> n >> m >> k;
    k++;
    if (k <= n) {
        cout << k << ' ' << 1 << '\n';
        return 0;
    }
    k--;
    ll c = (k-n)/(m-1);
    ll row = n - c;
    ll col = (c % 2 == 0) ? (k-n) % (m-1) + 2: m-((k-n) % (m-1));
    cout << row << ' ' << col << '\n';


    return 0;
}
	

