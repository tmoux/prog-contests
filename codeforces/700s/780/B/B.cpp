#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;
typedef long long ll;

const int maxn = 600005;
int pos[maxn], speed[maxn];
double eps = 1e-10;
int n;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> pos[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> speed[i];
    }
    double lo = 0.0, hi = 1e10;
    while (abs(lo-hi) > eps) {
        double mid = (lo+hi)/2;
        bool valid = true;
        pair<double,double> invl = {pos[0]-mid*speed[0],pos[0]+mid*speed[0]};
        for (int i = 1; i < n; i++) {
            pair<double,double> in2 = {pos[i]-mid*speed[i],pos[i]+mid*speed[i]};
            pair<double,double> newinvl = {max(invl.first,in2.first),min(invl.second,in2.second)};
            if (newinvl.first > newinvl.second) {
                valid = false;
                break;
            }
            else {
                invl = newinvl;
            }
        }
        if (valid) {
            hi = mid;
        }
        else {
            lo = mid;
        }
    }
    cout << fixed << setprecision(10) << lo << '\n';




    return 0;
}
	

