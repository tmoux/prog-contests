#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<int> verts(n);
    for (int i = 0; i < n; i++) cin >> verts[i];
    verts.push_back(1000000000);
    multiset<int> horiz;
    for (int i = 0; i < m; i++) {
        int x1, x2, y; cin >> x1 >> x2 >> y;
        if (x1 == 1) {
            horiz.insert(x2);
        }
    }

    sort(verts.begin(),verts.end());
    int res = 999999999;
    for (int i = 0; i < verts.size(); i++) {
        int v = verts[i];
        while (!horiz.empty() && *horiz.begin() < v) {
            horiz.erase(horiz.begin());
        }
        //cout << i << ' ' << (i + (int)(horiz.size())) << '\n';
        res = min(res,i+(int)horiz.size());
    }
    cout << res << '\n';


    return 0;
}
    
