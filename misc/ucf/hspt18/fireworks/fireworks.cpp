#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

double getheight(double t, int vi) {
    return 0.5*-9.81*t*t+(double)(vi)*t;    
}

double gettime(int vi) {
    return (double)(vi)/9.81;
}

int main()
{
    int t; cin >> t;
    for (int a = 1; a <= t; a++) {
        int n; cin >> n;
        vector<int> vel(n);
        for (int i = 0; i < n; i++) {
            cin >> vel[i];
        }
        double earliest = gettime(vel[0]);
        int earliestIdx = 0;
        double highest = getheight(gettime(vel[0]),vel[0]);
        int highestIdx = 0;
        for (int i = 0; i < n; i++) {
            double t = gettime(vel[i]);
            //cout << i << ": " << t << '\n';
            if (t < earliest) {
                earliest = t;
                earliestIdx = i;
            }
            double h = getheight(t,vel[i]);
            if (h > highest) {
                highest = h;
                highestIdx = i;
            }
        }
        printf("Scenario #%d:\n",a);
        printf("Highest Firework: %d\n",highestIdx+1);
        printf("Earliest Firework: %d\n",earliestIdx+1);
        printf("\n");
    }

    return 0;
}

