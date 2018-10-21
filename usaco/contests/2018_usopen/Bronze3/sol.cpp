#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    freopen("outofplace.in","r",stdin);
    freopen("outofplace.out","w",stdout);
    int n; cin >> n;
    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        B[i] = A[i];
    }
    sort(B.begin(),B.end());
    set<int> s;
    for (int i = 0; i < n; i++) {
        if (A[i] != B[i]) s.insert(A[i]);
    }
    cout << s.size() - 1 << '\n';

    return 0;
}
