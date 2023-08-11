#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<int> a;
    vector<int> extra;
    int b0 = 0, b1 = 0;
    while (n--) {
        a.clear();
        int k; cin >> k;
        for (int i = 0; i < k; i++) {
            int ai; cin >> ai;
            a.push_back(ai);
        }
        for (int i = 0; i < k/2; i++) {
            b0 += a[i];
        }
        for (int i = k%2==0?k/2:k/2+1; i < k; i++) {
            b1 += a[i];
        }
        if (k&1) extra.push_back(a[k/2]);
    }
    sort(extra.begin(),extra.end(),greater<int>());
    for (int i = 0; i < extra.size(); i++) {
        if (i % 2 == 0) b0 += extra[i];
        else b1 += extra[i];
    }
    cout << b0 << ' ' << b1 << '\n';
}

