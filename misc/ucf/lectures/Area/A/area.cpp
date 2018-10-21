#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <math.h>
using namespace std;
typedef long long ll;
const int MAXN = 50005;
const double EPS = 1e-10;

struct Vertex
{
    int x, y;
    
    Vertex() {
    }
    
    Vertex(int x0, int y0) : x(x0), y(y0) {
    }
    
    bool operator < (const Vertex &A) const
    {
        return x < A.x || (abs(x - A.x) <= EPS && y < A.y);
    }
    
    Vertex operator - (const Vertex &A)
    {
        return Vertex(x - A.x, y - A.y);
    }
    
}v[MAXN], ch[MAXN];

int Cross(Vertex A, Vertex B)
{
    return A.x * B.y - A.y * B.x;
}

int N;

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        v[i].x = x;
        v[i].y = y;
    }
    
    /*
    for (int i = 0; i < N; i++) {
        cout << v[i].x << " " << v[i].y << endl;
    }
    */
    sort(v,v+N);
    int m = 0;
    for (int i = 0; i < N; ++i)
    {
        while (m > 1 && Cross(ch[m - 1] - ch[m - 2], v[i] - ch[m - 2]) <= 0) m--;
        ch[m++] = v[i];
    }
    int k = m;
    for (int i = N - 2; i >= 0; --i)
    {
        while (m > k && Cross(ch[m - 1] - ch[m - 2], v[i] - ch[m - 2]) <= 0) m--;
        ch[m++] = v[i];
    }
    ll ans = 0;
    int j = m - 2;
    /*
    for (int i = 0; i < m - 1; i++) {
        cout << ch[i].x << ' ' << ch[i].y << '\n';
    }
    */
    for (int i = 0; i < m - 1; i++) {
        ans += (ll)(ch[j].x + ch[i].x) * (ch[j].y - ch[i].y);
        j = i;
    }
    cout << abs(ans) << '\n';
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
	
	return 0;
}
