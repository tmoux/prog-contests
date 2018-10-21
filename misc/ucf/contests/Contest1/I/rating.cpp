#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 500005;
int n, k;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(A.begin(),A.end());
    vector<int> pre(n);
    pre[0] = A[0];
    for (int i = 1; i < n; i++) {
        pre[i] = pre[i-1] + A[i];
    }
    int idx = 0;
    if (A[0] >= 0 || k == 0) {
        cout << 0 << '\n';
        return 0;
    }
    while (A[idx] < 0 && idx < k) {
        idx++;
    }
    cout << abs(pre[idx-1]) << '\n';



    return 0;
}
	

