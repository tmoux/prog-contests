#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;


int dist[8][8];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int perm[] = {0,1,2,3,4,5,6,7};
    memset(dist,-1,sizeof(dist));
    dist[0][1] = 100;
    dist[1][0] = 100;
    dist[0][2] = 150;
    dist[2][0] = 150;
    dist[1][2] = 80;
    dist[2][1] = 80;
    dist[1][4] = 120;
    dist[4][1] = 120;
    dist[4][5] = 90;
    dist[5][4] = 90;
    dist[2][5] = 150;
    dist[5][2] = 150;
    dist[2][3] = 60;
    dist[3][2] = 60;
    dist[3][6] = 100;
    dist[6][3] = 100;
    dist[5][6] = 90;
    dist[6][5] = 90;
    dist[5][7] = 80;
    dist[7][5] = 80;
    dist[6][7] = 100;
    dist[7][6] = 100;
    int minDist = 999999;
    do {
        int d = 0;
        for (int i = 0; i < 7; i++) {
            if (i < 6) {
                d += (dist[perm[i]][perm[i+1]] > 0 ? dist[perm[i]][perm[i+1]] : 999999);
            }
            else {
                d += (dist[perm[i]][perm[0]] > 0 ? dist[perm[i]][perm[0]] : 999999);
            }
        }
        minDist = min(minDist,d);
        cout << d << ' ' << minDist << '\n';
    } while (next_permutation(perm,perm+8));
    cout << minDist << '\n';

    return 0;
}
	

