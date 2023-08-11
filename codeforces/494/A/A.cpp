#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s;
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    n = s.size();
    bool poss = true;
    int last;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '#') {
            last = i;
            break;
        }
    }
    vector<int> ans;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            a[i] = 1;        
        }
        else if (s[i] == ')') {
            a[i] = -1;
        }
        else {
            if (i == last) {
                int pre = i == 0 ? 0 : a[i-1];
                int x = 0;
                for (int j = i + 1; j < n; j++) {
                    x += s[j] == '(' ? 1 : -1;
                }
                ans.push_back(pre+x);
                a[i] = -(pre+x);
            }
            else {
                ans.push_back(1);
                a[i] = -1;
            }
        }
        if (i > 0) a[i] += a[i-1];
    }
    for (int i = 0; i < n; i++) {
        if (a[i] < 0) {
            cout << -1 << '\n';
            return 0;
        }
    }
    //check if it's impossible
    if (a[n-1] != 0) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i: ans) {
        if (i <= 0) {
            cout << -1 << '\n';
            return 0;
        }
    }
    //now it is possible
    for (int i: ans) {
        cout << i << '\n';
    }

    return 0;
}

