#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll ch2[100005];
void solve(int n) {
    /*
    cout << "\n\n";
    cout << n << ": ";
    */
    int curr = 100000;
    vector<int> ans;
    while (n > 0) {
        while (ch2[curr] > n) {
            curr--;
        }
        n -= ch2[curr];
        //cout << curr << ": " << ch2[curr] << '\n';
        ans.push_back(curr);
    }
    ans.push_back(0);
    reverse(ans.begin(),ans.end());
    vector<int> v;
    for (int i = 1; i < ans.size(); i++) {
        v.push_back({ans[i]-ans[i-1]});
    }
    string res = "1";
    for (int i: v) {
        //cout << i << ' ';
        for (int j = 0; j < i; j++) {
            res += '3';
        }
        res += '7';
    }
    //cout << '\n';
    cout << res << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 1; i <= 100000; i++) {
        ch2[i] = 1LL*i*(i-1)/2;
    }
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        solve(n);
        //cout << solve(n) << '\n';
    }

}

