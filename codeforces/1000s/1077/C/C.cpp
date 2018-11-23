#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    multiset<int> ms;
    ll total = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        total += ai;
        a[i] = ai;
        ms.insert(ai);
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        total -= a[i];
        ms.erase(ms.find(a[i]));
        int me = *ms.rbegin();
        if (total - me == me) ans.push_back(i+1);
        total += a[i];
        ms.insert(a[i]);
    }
    //output
    cout << ans.size() << '\n';
    for (int i: ans) {
        cout << i << ' ';
    }

    return 0;
}

