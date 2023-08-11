#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    int numPos = 0;
    int numNeg = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > 0) numPos++;
        else if (a[i] < 0) numNeg++;
    }
    int numNeed = (n % 2 == 0 ? n/2 : n/2+1);
    if (numPos >= numNeed) {
        cout << 1 << '\n';
    }
    else if (numNeg >= numNeed) {
        cout << -1 << '\n';
    }
    else {
        cout << 0 << '\n';
    }
}

