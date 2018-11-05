#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int lo = 0, hi = n+1;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        cout << "? " << mid << endl;
        string r; cin >> r;
        if (r == "<") {
            hi = mid;    
        }
        else lo = mid;
    }
    cout << "! " << lo << endl;

    return 0;
}

