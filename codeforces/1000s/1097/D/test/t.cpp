#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
string st[maxn];
bool f[maxn];
int G[maxn*10];

int n;

int main()
{
    scanf("%d",&n);
    int mn;
    for (int i = 1; i <= n; i++) {
        cin >> st[i];
        mn = 999999;
        for (int j = 0; j < st[i].size(); j++) {
            if (st[i][j] == '(') {
                g[i]++;
            }
            else {
                g[i]--;
            }
            mn = min(mn,g[i]);
        }
        if (mn < g[i] && mn < 0) f[i] = 1;:w
    }

    return 0;
}

