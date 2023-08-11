#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, k, s;
int move(int curr, int dist) {
    if (curr + dist <= n) {
        return curr + dist;
    }
    else return curr - dist;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> s;
    if ((n-1) * k < s || k > s) {
        cout << "NO" << '\n';
        return 0;
    }
    cout << "YES" << '\n';
    int curr = 1;
    while (k) {
        //move a lot
        int dist = min(n-1,s-k+1);
        curr = move(curr,dist);
        k--;
        s -= dist;
        cout << curr << ' ';
        //cout << "dist: " << dist << '\n';
    }

    return 0;
}
	

