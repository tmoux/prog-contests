#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> m >> n;
    vector<int> cycle;
    for (int i = 0; i < n; i++) {
        cout << 1 << endl;
        int res; cin >> res;
        if (res == 0) {
            return 0;
        }
        else {
            if (res == 1) {
                //telling the truth
                cycle.push_back(1);
            }
            else {
                cycle.push_back(0);
            }
        }
    }
    //used up n guesses
    int lo = 1, hi = m;
    for (int i = 0; i < 60-n; i++) {
        int mid = (lo + hi + 1) / 2;
        cout << mid << endl;
        int res; cin >> res;
        if (res == 0) {
            return 0;
        }
        if (cycle[i%n] == 0) {
            res *= -1;
        }
        if (res == 1) {
            lo = mid;
        }
        else {
            hi = mid;
        }
    }

    return 0;
}
	
