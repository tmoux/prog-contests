#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    deque<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int curr = 0;
    vector<char> ans;
    while (!a.empty()) {
        int mn = min(a.front(),a.back());
        if (curr < a.front() && a.front() == a.back()) {
            int l = 0, r = 0;
            for (int i = 0; i < a.size(); i++) {
                if (i == 0 || a[i] > a[i-1]) l++;
                else break;
            }
            for (int i = a.size()-1; i >= 0; i--) {
                if (i == a.size()-1 || a[i] > a[i+1]) r++;
                else break;
            }
            if (l > r) {
                for (int i = 0; i < l; i++) {
                    ans.push_back('L');
                }
            }
            else {
                for (int i = 0; i < r; i++) {
                    ans.push_back('R');
                }
            }
            break;
        }
        else {
            if (mn > curr) {
                char c = a.front() == mn ? 'L' : 'R';
                if (c == 'L') a.pop_front();
                else a.pop_back();
                ans.push_back(c);
                curr = mn;
            }
            else {
                if (a.front() > curr) {
                    curr = a.front();
                    a.pop_front();
                    ans.push_back('L');
                }
                else if (a.back() > curr) {
                    curr = a.back();
                    a.pop_back();
                    ans.push_back('R');
                }
                else break;
            }
        }
    }
    cout << ans.size() << '\n';
    for (char c: ans) {
        cout << c;
    }
    cout << '\n';

    return 0;
}

