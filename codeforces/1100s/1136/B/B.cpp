#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
int n, k;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    int ans = 2*n + 1;
    int add = min(max(0,k-1),max(0,n-k)) + (n-1);
    cout << (ans+add) << '\n';
}

