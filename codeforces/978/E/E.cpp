#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n, w;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> w;
    int minD, maxD;
    int curr = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        curr += ai;
        if (i == 0) {
            minD = curr;
            maxD = curr;
        }
        else {
            minD = min(minD,curr);
            maxD = max(maxD,curr);
        }
    }

    int x = max(0,-minD);
    int y = min(w,w - maxD);
    if (0 <= x && x <= w && 0 <= y && y <= w && x <= y) {
        int invl = y-x+1;
        cout << max(invl,0) << '\n';
    }
    else {
        cout << 0 << '\n';
    }


    return 0;
}
	

