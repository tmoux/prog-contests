#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 4e5+5;
int n;
vector<int> a;

vector<int> pos[25];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }

}

