#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int prev[maxn], need[maxn];

void solve(int qq) {
    int N, L; cin >> N >> L;
    memset(prev,-1,sizeof prev);    
    memset(need,-1,sizeof need);    
    for (int i = N-1; i >= 0; i--) {
        double percent = 100*(double)(i)/(double)(N);
        if (
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        solve(qq);
    }
}

