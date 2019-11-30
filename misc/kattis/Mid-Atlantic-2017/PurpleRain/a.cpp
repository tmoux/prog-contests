#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int pre[maxn];
int n;
string s;

pair<int,pair<int,int>> solve() {
    pair<int,int> mn = {maxn,-1};
    pair<int,pair<int,int>> ret = {-1,{-1,-1}};
    for (int i = 1; i <= n; i++) {
        pre[i] = s[i-1]=='B'?1:-1;
        pre[i] += pre[i-1];
        mn = min(mn,{pre[i-1],i});
        if (pre[i] - mn.first > ret.first) {
            ret = {pre[i]-mn.first,{mn.second,i}};
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    n = s.size();
    auto ans = solve();
    for (char& c: s) {
        c = c=='B'?'R':'B';
    }
    auto p = solve();
    if (p.first > ans.first) {
        ans = p;
    }
    else if (p.first == ans.first) {
        if (p.second.first < ans.second.first) {
            ans = p;
        }
        else if (p.second.first == ans.second.first) {
            if (p.second.second < ans.second.second) {
                ans = p;
            }
        }
    }
    cout << ans.second.first << ' ' << ans.second.second << '\n';
}

