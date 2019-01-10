#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int h1, w1, h2, w2; cin >> h1 >> w1 >> h2 >> w2;
    int lose1 = (h1-1)*w2;
    int lose2 = (h2-1)*w1;
    if (lose1 > lose2) {
        cout << 1 << '\n';
    }
    else if (lose1 < lose2) {
        cout << 2 << '\n';
    }
    else {
        cout << -1 << '\n'; 
    }

    return 0;
}

