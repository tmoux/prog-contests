#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const ll maxn = 100005;
const ll INF = 2000000000;
ll n, pre[maxn];
struct Point {ll x, y;};
Point A[maxn];
ll square(ll x) {return x*x;};
bool compX(const Point& a, const Point& b) {
    return a.x < b.x;
}
bool compY(const Point& a, const Point& b) {
    return a.y < b.y;
}
ll dist(const Point& a, const Point& b) {
    return square(a.x-b.x) + square(a.y-b.y);
}
ll smalldist(int start, int end) {
    ll ans = INF;
    for (int i = start; i <= end; i++) {
        for (int j = i + 1; j <= end; j++) {
            ans = min(ans,dist(A[i],A[j]));
        }
    }
    return ans;
}

ll closestPoint(int start, int end) {
    if (end - start + 1 <= 3) {
        return smalldist(start, end);
    }
    ll mid = (start+end)/2;
    ll dl = closestPoint(start,mid);
    ll dr = closestPoint(mid+1,end);
    ll d = min(dl,dr);
    vector<Point> strip;
    for (int i = start; i <= end; i++) {
        if (square(A[i].x-A[mid].x) < d) {
            strip.push_back(A[i]);
        }
    }
    sort(strip.begin(),strip.end(),compY);
    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size() && square(strip[i].y-strip[j].y) < d; j++) {
            d = min(d,dist(strip[i],strip[j]));
        }
    }
    return d;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> pre[i];
        pre[i] += pre[i-1];
        A[i] = {i,pre[i]};
    }
    sort(A+1,A+n+1,compX);
    ll ans = closestPoint(1,n); 
    cout << ans << '\n';

    return 0;
}
	

