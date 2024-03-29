#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int c1 = 0, c2 = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 1) c1++;
        else c2++;
    }
    int curr = 0;
    vector<int> ans;
    while (c1 > 0 || c2 > 0) {
        if (curr&1 || curr == 0) {
            if (c2 > 0) {
                curr += 2;
                c2--;
                ans.push_back(2);
            }
            else {
                curr++;
                c1--;
                ans.push_back(1);
            }
        }
        else {
            if (c1 > 0) {
                curr++;
                c1--;
                ans.push_back(1);
            }
            else {
                curr += 2;
                c2--;
                ans.push_back(2);
            }
        }
    }
    for (int i: ans) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}

