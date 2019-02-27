#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("in","r",stdin);
    int w1, h1, w2, h2; cin >> w1 >> h1 >> w2 >> h2;
    int area = (w1+2) * (h1+2) + (w2+2) * (h2+2) - (w1*h1) - (w2*h2);
    //cout << area << '\n';
    area -= 2 * min(w1+2,w2+2);
    cout << area << '\n';

    return 0;
}