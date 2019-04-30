#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    int a, b, c, d; cin >> a >> b >> c >> d;
    int mx = max(max(a,b),max(c,d));
    vector<int> v;
    v.push_back(mx-a);
    v.push_back(mx-b);
    v.push_back(mx-c);
    v.push_back(mx-d);
    sort(v.begin(),v.end(),greater<int>());
    printf("%d %d %d\n",v[0],v[1],v[2]);
    return 0;
}

