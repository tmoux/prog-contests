#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, h, a, b, k;

int query(int ta, int fa, int tb, int fb) {
    if (ta == tb) {
        cout << abs(fa-fb) << '\n';
        return 0;
    }
    if (fa > b) {
        int res = fa-b;
        res += abs(ta-tb);
        res += abs(fb-b);
        cout << res << '\n';
        return 0;
    }
    else if (fa < a) {
        int res = a - fa;
        res += abs(ta-tb);
        res += abs(fb-a);
        cout << res << '\n';
        return 0;
    }
    else {
        int res = abs(ta-tb);
        res += abs(fa-fb);
        cout << res << '\n';
        return 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> h >> a >> b >> k;
    for (int i = 0; i < k; i++) {
        int ta, fa, tb, fb; cin >> ta >> fa >> tb >> fb;
        query(ta,fa,tb,fb);
    }

    return 0;
}
	

