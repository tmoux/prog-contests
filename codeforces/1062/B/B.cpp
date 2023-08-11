#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int ceil(int x) {
    int r = 0;
    while (1 << r < x) {
        r++;
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int ans = 1;
    int maxf = 0;
    vector<int> facs;
    for (int i = 2; i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                n /= i;
                cnt++;
            }
            ans *= i;    
            int r = ceil(cnt);
            maxf = max(maxf,r);
            facs.push_back(cnt);
            //cout << i << ": " << cnt << '\n';
        }
    }
    bool add = false;
    for (int i: facs) {
        if (i < (1 << maxf)) {
            add = true;
            break;
        }
    }

    /*
    cout << maxf << '\n';
    cout << "add = " << add << '\n';
    */
    cout << ans << ' ' << (maxf + (add ? 1 : 0)) << '\n';


    return 0;
}

