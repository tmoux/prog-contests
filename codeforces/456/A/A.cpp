#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    while (n--) {
        int ai, bi; cin >> ai >> bi;
        if (ai != bi) {
            cout << "Happy Alex\n";
            return 0;
        }
    }
    cout << "Poor Alex\n";


    return 0;
}
	

