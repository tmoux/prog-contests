/*
ID: silxikys
PROG: fc
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
#include <array>
#include <chrono>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

const int MAXN = 10005;
const double EPS = 1e-10;

struct Vertex
{
    double x, y;
    
    Vertex() {
    }
    
    Vertex(double x0, double y0) : x(x0), y(y0) {
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

double Cross(Vertex A, Vertex B)
{
    return A.x * B.y - A.y * B.x;
}

double sqr(double x)
{
    return x * x;
}

double Distance(Vertex A, Vertex B)
{
    return sqrt(sqr(A.x - B.x) + sqr(A.y - B.y));
}

int N;

int main() {
    //freopen("fc.in","r",stdin); freopen("fc.out","w",stdout);

	cin >> N;
	for (int i = 0; i < N; i++) {
		double x, y; cin >> x >> y;
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
    double ans = 0;
    for (int i = 0; i < m - 1; ++i)
        ans += Distance(ch[i], ch[i + 1]);
    cout << fixed << setprecision(2) << ans << endl;
	
    for (int i = 0; i < m - 1; i++) {
        cout << ch[i].x << ' ' << ch[i].y << '\n';
    }
	return 0;
}