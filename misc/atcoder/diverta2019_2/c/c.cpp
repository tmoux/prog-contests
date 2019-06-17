#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N;
ll A[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    sort(A,A+N,greater<int>());
    ll res = 0;
    res += A[0];
    for (int i = 1; i < N-1; i++) {
        res += abs(A[i]);
    }
    res -= A[N-1];
    cout << res << '\n';
    int idx = 1;
    ll curr = A[N-1];
    for (; idx < N - 1 && A[idx] >= 0; idx++) {
        cout << A[N-1] << ' ' << A[idx] << '\n';
        A[N-1] -= A[idx];
    }
    //cerr << idx << ' ' << A[idx] << '\n';
    cout << A[0] << ' ' << A[N-1] << '\n';
    A[0] -= A[N-1];
    for (; idx < N - 1; idx++) {
        cout << A[0] << ' ' << A[idx] << '\n';
        A[0] -= A[idx];
    }
}

