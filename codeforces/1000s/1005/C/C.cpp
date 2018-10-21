#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<int,int> mp;
int n;
ll A[120005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        mp[A[i]]++;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 31; (ll)(1LL << j) > A[i]; j--) {
            ll diff = (ll)(1LL << j) - A[i];
            //cout << A[i] << ' ' << diff << '\n';
            if (mp.count(diff) && (mp[diff] > 1 || 2*A[i] != (1LL << j))) {
                found = true;
                break;
            }
        }
        if (!found) ans++;
    }
    cout << ans << '\n';


    return 0;
}
	

