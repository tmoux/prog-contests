#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
int n, m, d;
int potential[maxn], club[maxn];
multiset<int> clubs[maxn];


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> potential[i];
    for (int i = 1; i <= n; i++) cin >> club[i];
    for (int i = 1; i <= n; i++) {
        clubs[club[i]].insert(potential[i]);
    }

}

