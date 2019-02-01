#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, M = 1e9+7;
int n;
vector<int> dir[maxn];
int isBlack[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n-1; i++) {
        int pi; cin >> pi;
        dir[pi].push_back(i);
    }
    for (int i = 0; i < n; i++) cin >> isBlack[i];


    return 0;
}

