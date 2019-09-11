#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 25;
int N, A[maxn], B[maxn], C[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> B[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> C[i];
    }
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        int curr = A[i];
        sum += B[curr];
        if (i > 1 && A[i-1] == A[i] - 1) {
            sum += C[A[i-1]];
        }
    }
    cout << sum << '\n';
}

