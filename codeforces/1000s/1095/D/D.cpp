#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n;
pair<int,int> a[maxn];

bool has(pair<int,int> p, int x) {
    return p.first == x || p.second == x;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    int curr = 1, nxt;
    if (has(a[a[1].first],a[1].second)) {
        nxt = a[1].first;    
    }
    else nxt = a[1].second;
    vector<int> ans;
    ans.push_back(curr);
    ans.push_back(nxt);
    for (int i = 0; i < n - 2; i++) {
        int p1 = ans[ans.size()-2];
        int p2 = ans[ans.size()-1];
        int nxt;
        if (p2 == a[p1].first) {
            nxt = a[p1].second;
        }
        else {
            nxt = a[p1].first;
        }
        ans.push_back(nxt);
    }
    //output
    for (int i: ans) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}

