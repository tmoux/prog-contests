#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll A, B; cin >> A >> B;
    vector<pair<char,char>> ans;
    while (A != B) {
        if (A % 2 == 0) {
            A /= 2;
            ans.push_back({'B','B'});
        }
        else if (B % 2 == 0) {
            B /= 2;
            ans.push_back({'A','A'});
        }
        else {
            if (A > B) {
                A += B;
                ans.push_back({'A','B'});
                A /= 2;
                ans.push_back({'B','B'});
            }
            else {
                B += A;
                ans.push_back({'B','A'});
                B /= 2;
                ans.push_back({'A','A'});
            }
        }
    }
    cout << ans.size() << '\n';
    for (auto p: ans) {
        cout << p.first << "+=" << p.second << '\n';
    }
}
