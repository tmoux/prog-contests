#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    vector<int> pre(n);
    pre[n-1] = A[n-1];
    for (int i = n - 2; i >= 0; i--) {
        pre[i] = min(A[i],pre[i+1]);
    }
    for (int i = 0; i < n; i++) {
        auto it = upper_bound(pre.begin()+i,pre.end(),A[i]-1);
        int x = distance(pre.begin()+i,it);
        cout << (x == 0 ? -1 : x-2) << ' ';
    }
    /*
    for (int i = 0; i < n; i++) {
        cout << pre[i] << ' ';
    }
    */

    return 0;
}

