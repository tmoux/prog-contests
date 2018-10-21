#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int hh, mm;
    cout << fixed << setprecision(10);
    double H, D, C, N;
    cin >> hh >> mm >> H >> D >> C >> N;
    if (hh >= 20) {
        cout << (ceil(H/N)*0.8*C) << '\n';        
    }
    else {
        double now = ceil(H/N)*C;
        int time = (19-hh)*60+(60-mm);
        double discount = ceil((H+time*D)/N)*0.8*C;
        cout << min(now,discount) << '\n';
    }


    return 0;
}
	

