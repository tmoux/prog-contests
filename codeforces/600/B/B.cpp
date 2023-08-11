#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, m, A[maxn];
pair<int,int> B[maxn];
int ans[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < m; i++) {
        cin >> B[i].first;
        B[i].second = i;
    }
    sort(A,A+n);
    sort(B,B+m);
    int L = 0;
    for (int i = 0; i < m; i++) {
        while (L < n && A[L] <= B[i].first) L++;        
        ans[B[i].second] = L;
    }
    //output
    for (int i = 0; i < m; i++) {
        cout << ans[i] << (i == m - 1 ? '\n' : ' ');
    }

    return 0;
}

