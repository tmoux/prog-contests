#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("fencedin.in","r",stdin); freopen("fencedin.out","w",stdout);
    int N, M, A, B;
    cin >> A >> B >> N >> M;
    vector<int> VA(N+1);
    vector<int> HA(M+1);
    for (int i = 0; i < N; i++) {
        cin >> VA[i];
    }
    for (int j = 0; j < M; j++) {
        cin >> HA[j];
    }
    sort(VA.begin(), VA.end());
    for (int i = 0; i < N; i++) {
        VA[i] = VA[i+1] - VA[i];
    }
    VA[N] = B - VA[N];
    sort(HA.begin(), HA.end());
    for (int i = 0; i < M; i++) {
        HA[i] = HA[i+1] - HA[i];
    }
    HA[M] = A - HA[M];
    sort(VA.begin(),VA.end());
    sort(HA.begin(),HA.end());
    N++; M++;

    ll res = 1LL*VA[0]*(M-1) + 1LL*HA[0]*(N-1);
    for (int vi = 1, hi = 1; vi < N && hi < M;) {
        if (VA[vi] < HA[hi]) {
            res += VA[vi++] * (M-hi);
        }
        else {
            res += HA[hi++] * (N-vi);
        }
    }
    cout << res << '\n';

    return 0;
}

