#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(A.begin(),A.end());
    int res = 0;
    for (int i = 1; i < n; i++) {
        if (A[i-1] < A[i] - 1) res += A[i] - A[i-1] - 1;
    }
    cout << res << '\n';

    return 0;
}

