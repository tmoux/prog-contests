#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxm = 100005;
int n, k, l;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> l;
    multiset<int> s;
    for (int i = 0; i < n*k; i++) {
        int ai; cin >> ai;
        s.insert(ai);
    }
    int mn = *s.begin();
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        auto it = s.upper_bound(mn+l);
        if (it == s.begin()) {
            cout << 0 << '\n';
            return 0;
        }
        multiset<int> ms;
        ms.insert(*prev(it));
        s.erase(prev(it));
        for (int j = 0; j < k-1; j++) {
            ms.insert(*prev(s.end()));
            s.erase(prev(s.end()));
        }
        ans += *ms.begin();
    }
    cout << ans << endl;
}
