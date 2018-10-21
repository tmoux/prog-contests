#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5;
int n, starts[maxn], endss[maxn];
multiset<int> s, e;

int main()
{
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        int ss, ee; scanf("%d %d",&ss,&ee);
        starts[i] = ss; endss[i] = ee;
        s.insert(ss);
        e.insert(ee);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        auto it1 = s.find(starts[i]);
        auto it2 = e.find(endss[i]);
        s.erase(it1);
        e.erase(it2);
        int r = (*e.begin()) - (*s.rbegin());
        ans = max(ans,r);
        s.insert(starts[i]);
        e.insert(endss[i]);
    }
    printf("%d\n",ans);

    return 0;
}
	

