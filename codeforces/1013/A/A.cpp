#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int xsum = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        xsum += ai;
    }
    int ysum = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        ysum += ai;
    }

    if (xsum >= ysum) {
        cout << "Yes" << '\n';
    }
    else {
        cout << "No" << '\n';
    }

    return 0;
}
	

