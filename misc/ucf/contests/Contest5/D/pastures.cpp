#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n, k;
struct Edge
{
    int u, v, pi;
    bool operator<(const Edge& rhs) const {
        return pi < rhs.pi;
    }
};

bool used[10005];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    vector<Edge> p(n-1);
    for (int i = 0; i < n - 1; i++) {
        cin >> p[i].u >> p[i].v >> p[i].pi;
    }
    sort(p.begin(),p.end());
    ll ans = 0;
    for (int i = p.size() - 1; i >= 0; i--) {
        if (!used[p[i].u]) {
            used[p[i].u] = true;
            k--;
        }
        if (!used[p[i].v]) {
            used[p[i].v] = true;
            k--;
        }
        if (k < 0) break;
        else {
            ans += p[i].pi;
        }
    }
    cout << ans << '\n';
   


    return 0;
}
	

