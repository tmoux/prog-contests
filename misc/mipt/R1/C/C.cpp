#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int root(int x) {
    int r = (int)sqrt(x);
    for (int i = max(1,r-3); i <= r+3; i++) {
        if (i*i == x) return i;
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int m; cin >> m;
    int n = root(m);
    vector<int> a(m);
    map<int,int> ncnt;
    vector<int> roots;
    vector<pair<int,int>> ans;
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        ncnt[a[i]]++;
    }
    auto p = ncnt.begin();
    ans.push_back({root(p->first),root(p->second)});
    ncnt[p->first] = 0;
    for (auto& p: ncnt) {
        if (p.second == 0) continue;
        bool found = false;
        int newfac, cnt;
        for (auto i: ans) {
            if (p.first % i.first == 0) {
                newfac = p.first/i.first;
                cnt = p.second/i.second/2;
                found = true;
                break;
            }
        }
        if (!found) {
            newfac = root(p.first);
            cnt = root(p.second);
        }
        ncnt[newfac*newfac] -= cnt*cnt;
        for (auto i: ans) {
            ncnt[i.first*newfac] -= 2*i.second*cnt;    
        }
        ans.push_back({newfac,cnt});
    }
    for (auto i: ans) {
        for (int a = 0; a < i.second; a++) {
            cout << i.first << ' ';
        }
    }


    return 0;
}

