#include <bits/stdc++.h>
#define pi 3.14159265359

using namespace std;

double circDist(double angle1, double angle2, double radius)
{
    double circ = 2.0 * radius * pi;

    //find the smallest of the two angles between the two houses
    double between_angle1 = angle1 - angle2;
    double between_angle2 = angle2 - angle1;

    if(between_angle1 < 0) between_angle1+=360.0;
    if(between_angle2 < 0) between_angle2+=360.0;

    //the distance will be the ratio between the smallest angle and 360
    //time the circumference
    double angle_between = min(between_angle1, between_angle2);

    return circ * (angle_between / 360.0);
}


int main()
{
    int t;cin >> t;
    for(int tree = 1; tree <= t; tree++)
    {
        double r; cin >> r;
        int c; cin >> c;
        vector<double> angles(c);

        for(int i =0; i < c; i++) cin >> angles[i];

        //brute force answer trying to set the bunker at each caterpillars' house

        double best_ans = 2000000000;
        for(int i = 0; i < c; i++)
        {
            double cur_ans = 0;

            for(int  j = 0; j < c; j++)
            {

                cur_ans += circDist(angles[i], angles[j], r);

            }

            best_ans = min(best_ans, cur_ans);
        }

        printf("Tree #%d: %.3f\n", tree, best_ans);
    }
    return 0;
}
/*

2
1 4
0.0 180.0 90.0 315.0
10 3
33.96 63.96 93.96

*/
