#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, d[maxn];

vector<pair<int,int>> ans;

void add(int a, int b) {
    ans.push_back({a,b});
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    vector<int> v;
    for (int i = 1; i <= 2*n; i += 2) {
        v.push_back(i);
    }
    sort(v.begin(),v.end(),[](auto a, auto b) {
            return d[(a+1)/2] > d[(b+1)/2];
            });
    for (int i = 0; i < n-1; i++) {
        add(v[i],v[i+1]);
    }
    for (int i = 0; i < n; i++) {
        int c = v[i];
        int dist = v.size()-i;
        add(c+1,v[i+d[(c+1)/2]-1]);
        if (d[(c+1)/2] == dist) {
            v.push_back(c+1);
        }
    }
    //output
    for (auto p: ans) {
        cout << p.first << ' ' << p.second << '\n';
    }
}

