#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <deque>
using namespace std;
typedef long long ll;

struct pii
{
    int x, y, idx;
};
const int maxn = 100005;
pii A[maxn];
int ans[maxn];
int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        A[i] = {x,y,i};
    }
    
    while (true) {
        random_shuffle(A,A+n);
        ll X = 0, Y = 0;
        for (int i = 0; i < n; i++) {
            ll x=A[i].x;
            ll y=A[i].y;
            ll x1 = X - x, y1 = Y - y, x2 = X + x, y2 = Y+y;
            if (x1*x1+y1*y1 < x2*x2+y2*y2)
            {
                X = x1, Y = y1;
                ans[A[i].idx] = -1;
            }
            else {
                X = x2, Y = y2;
                ans[A[i].idx] = 1;
            }
        }
        if (X*X + Y*Y <= 2000000000000LL) {
            //valid answer
            for (int i = 0; i < n; i++) {
                cout << ans[i] << ' ';
            }
            return 0;
        }
    }

    

    return 0;
}
	

