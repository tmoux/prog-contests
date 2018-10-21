#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

pair<int,int> dir[4] = {{1,0},{0,-1},{-1,0},{0,1}};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x, n; cin >> x >> n;
    int xpos = 0, ypos = 0;
    for (int i = 0; i < n; i++) {
        int m = i % 4;
        xpos += dir[m].first * x;
        ypos += dir[m].second * x;
        x++;
    }

    cout << xpos << ' ' << ypos << '\n';

    return 0;
}
	

