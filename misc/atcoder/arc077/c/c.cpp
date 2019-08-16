#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    deque<int> ans;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if (i % 2 == 0) ans.push_back(ai);
        else ans.push_front(ai);
    }
    if (n&1) reverse(ans.begin(),ans.end());
    for (int i: ans) {
        cout << i << ' ';
    }
    cout << '\n';
}

