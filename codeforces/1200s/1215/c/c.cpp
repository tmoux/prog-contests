#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
string s, t;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s >> t;
    int ab = 0, ba = 0;
    vector<int> vab, vba;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a' && t[i] == 'b') {
            ab++;
            vab.push_back(i);
        }
        else if (s[i] == 'b' && t[i] == 'a') {
            ba++;
            vba.push_back(i);
        }
    }
    if ((ab + ba) % 2 != 0) {
        cout << -1 << '\n';
        return 0;
    }
    vector<pair<int,int>> ans;
    //cout << vab.size() << ' ' << vba.size() << endl;
    if (ab % 2 == 1) {
        //do one switch
        int p = vab.back();
        vab.pop_back();
        vba.push_back(p);
        ans.push_back({p,p});
    }
    assert(vab.size() % 2 == 0 && vba.size() % 2 == 0);
    while (!vab.empty()) {
        int a1 = vab.back();
        vab.pop_back();
        int a2 = vab.back();
        vab.pop_back();
        ans.push_back({a1,a2});
    }
    while (!vba.empty()) {
        int a1 = vba.back();
        vba.pop_back();
        int a2 = vba.back();
        vba.pop_back();
        ans.push_back({a1,a2});
    }

    //output
    cout << ans.size() << '\n';
    for (auto p: ans) {
        cout << (p.first+1) << ' ' << (p.second+1) << '\n';
    }
}

