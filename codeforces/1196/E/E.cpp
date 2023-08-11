#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int b, w; cin >> b >> w;
        vector<pair<int,int>> ans;
        int curr = 2;
        int shift = 0;
        //assume b >= w
        if (w > b) {
            swap(w,b);
            shift = 1;
        }
        while (true) {
            if (w > 0) {
                ans.push_back({2,curr});
                w--;
                curr++;
            }
            else break;
            if (b > 0) {
                ans.push_back({2,curr});
                b--;
                curr++;
            }
            else break;
        }
        if (b > 0) {
            for (int i = 2; i < curr && b > 0; i += 2,b--) {
                ans.push_back({1,i});
            }
            for (int i = 2; i < curr && b > 0; i += 2,b--) {
                ans.push_back({3,i});
            }
            if (b > 0) {
                ans.push_back({2,1});
                b--;
            }
        }

        //output
        if (b == 0 && w == 0) {
            cout << "YES\n";
            for (auto p: ans) {
                cout << p.first << ' ' << (p.second+shift) << '\n';
            }
        }
        else {
            cout << "NO\n";
        }
    }
}

