#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m, a[maxn];
vector<int> at[maxn];

int dist(int a, int b) {
    if (b-a >= 0) return b-a;
    return m - (a-b);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i]--;
        at[a[i]].push_back(i);
    }
    int active = 0;
    int x = 0;
    ll currAns = 0;
    for (int i = 1; i < n; i++) {
        if (1 + dist(x,a[i+1]) <= dist(a[i],a[i+1])) {
            currAns += 1 + dist(x,a[i+1]);
            active++;
        }
        else {
            currAns += dist(a[i],a[i+1]);
        }
    }
    ll bestAns = currAns;
    for (int x = 1; x < m; x++) {
        for (int i: at[x-1]) {
            if (i-1 > 0) {
                currAns--;
                currAns += dist(a[i-1],a[i]);
                active--;
            }
        }
        currAns -= active;
        for (int i: at[x-1]) {
            if (i+1 <= n) {
                active++;
            }
        }
        //cout << x << ": " << currAns << '\n';
        //cout << "active = " << active << '\n';
        bestAns = min(bestAns,currAns);
    }
    cout << bestAns << '\n';
}

