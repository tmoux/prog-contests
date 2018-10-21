#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5, maxk = 19;
int n, q, A[maxn];
int rm[maxk][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        if (A[i] == 0) A[i] = maxn + 5;
    }


    return 0;
}

