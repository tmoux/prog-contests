#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    if (m < n - 1) {
        cout << "Impossible\n";
        return 0;
    }
    vector<pair<int,int>> v;
    for (int i = 1; i <= n && m > 0; i++) {
        for (int j = i + 1; j <= n && m > 0; j++) {
            if (__gcd(i,j) == 1) {
                v.push_back({i,j});
                m--;
            }
        }
    }
    if (m > 0) {
        cout << "Impossible\n";
        return 0;
    }
    cout << "Possible\n";
    for (auto p: v) {
        cout << p.first << ' ' << p.second << '\n';
    }


    return 0;
}
	

