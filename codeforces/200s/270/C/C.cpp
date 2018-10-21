#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, m, A[maxn], pre[maxn];
int inflect[maxn], deflect[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    for (int i = 2; i <= n-1; i++) {
        inflect[i] += inflect[i-1];
        if (!(A[i-1] == A[i] && A[i] == A[i+1])) {
            if (A[i] >= A[i-1] && A[i] >= A[i+1]) {
                inflect[i]++;
            }
        }
        deflect[i] += deflect[i-1];
        if (!(A[i-1] == A[i] && A[i] == A[i+1])) {
            if (A[i] <= A[i-1] && A[i] <= A[i+1]) {
                deflect[i]++;
            }
        }

        cout << i << ' ' << inflect[i] << '\n';
    }
    

    return 0;
}
	

