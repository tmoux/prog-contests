#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool hasDistinct(int y) {
    vector<bool> has(10,false);
    while (y) {
        int x = y % 10;
        if (has[x]) return true;
        has[x] = true;
        y /= 10;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int y; cin >> y;
    y++;
    while (hasDistinct(y)) y++;
    cout << y << '\n';

    return 0;
}

