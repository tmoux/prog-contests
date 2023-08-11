#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

struct Time
{
   int hr, min; 
   Time operator+(int i) {
       Time res = {hr,min+i};
       while (res.min >= 60) {
           res.min -= 60;
           res.hr++;
       }
       return res;
   }

   bool operator<(const Time& rhs) {
       if (hr != rhs.hr) {
           return hr < rhs.hr;
       }
       return min < rhs.min;
   }

   void print() {
       cout << hr << ' ' << min << '\n';
   }
};

Time arr[105];
int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("input.in","r",stdin);
    int n, s;
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
       int h, m; cin >> h >> m;
       arr[i] = {h,m};
    }
    Time test = {0,0};
    if (test + s < arr[0]) {
        test.print();
        return 0;
    }
    for (int i = 0; i < n; i++) {
        Time poss = arr[i] + (s+1);
        if (i == n - 1 || poss + s < arr[i+1]) {
            poss.print();
            break;
        }
    }

    
    return 0;
}
	

