#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int A[maxn], B[maxn];
int N;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        A[i] = 9999999;
    }
    for (int i = 2; i <= N; i++) {
        cin >> B[i];
        A[i] = min(A[i],B[i]);
        A[i-1] = min(A[i-1],B[i]);
    }
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        sum += A[i];
    }
    cout << sum << '\n';
}

