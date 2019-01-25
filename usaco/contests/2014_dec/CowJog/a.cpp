#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N, T, m[maxn], b[maxn];

int main()
{
    freopen("cowjog.in","r",stdin); freopen("cowjog.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> T;
    for (int i = 0; i < N; i++) {
        cin >> b[i] >> m[i];
    }
    multiset<ll> lines;
    lines.insert(1LL*T*m[0]+b[0]);
    for (int i = 1; i < N; i++) {
        ll t = 1LL*T*m[i]+b[i];
        auto it = lines.lower_bound(t);
        if (it == lines.begin()) {
            //add a new line
            lines.insert(t);    
        }
        else {
            --it;
            lines.erase(it);
            lines.insert(t);
        }
    }
    cout << lines.size() << '\n';

    return 0;
}

