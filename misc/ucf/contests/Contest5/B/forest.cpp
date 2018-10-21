#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <math.h>
#include <iomanip>
using namespace std;
typedef long long ll;
const int MAXN = 50005;
const double EPS = 1e-10;
const double PI = 3.141592653589793;
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

double Magnitude(Vertex A) {
    return sqrt(A.x*A.x + A.y*A.y);    
}

int N, C;

void solve() {
    cin >> N >> C;
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
    double area1 = 0;
    int j = m - 2;
    for (int i = 0; i < m - 1; i++) {
        area1 += (ch[j].x + ch[i].x) * (ch[j].y - ch[i].y);
        j = i;
    }
    area1 = abs(area1)/2;
   

    double perim1 = 0.0;
    for (int i = 0; i < m - 1; i++) {
        perim1 += Magnitude(ch[i] - ch[i+1]);
    }

    area1 += perim1*C;

    double newarea = area1 + (C*C)*PI;
    double newperim = perim1 + C*2*PI;
    cout << fixed << setprecision(2) << newperim << ' ' << newarea << '\n';
}

int main() {
    solve(); 
	return 0;
}

