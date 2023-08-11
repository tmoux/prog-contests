#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
const int INF = 2000000000;
int n, m, numElev, numStairs, v;
vector<int> elevators, stairs;

int getDistance(int y1, int y2, int med) {
    return abs(y1-med) + abs(med-y2);
}

int getClosest(int y1, int y2, const vector<int>& vec) {
    if (vec.size() == 0) {
        return INF;
    }
    //now we know there is at least one element in vec
    if (y1 > y2) {
        swap(y1,y2);
    }
    int ret = INF;
    auto t1 = lower_bound(vec.begin(),vec.end(),y1);
    if (t1 != vec.end()) {
        ret = min(ret,getDistance(y1,y2,*t1));
    }
    auto t2 = upper_bound(vec.begin(),vec.end(),y2);
    if (t2 != vec.end()) {
        ret = min(ret,getDistance(y1,y2,*t2));
    }
    auto t3 = lower_bound(vec.begin(),vec.end(),y1);
    if (t3 != vec.begin()) {
        t3--;
        ret = min(ret,getDistance(y1,y2,*t3));
    }
    return ret;
}
int elevatorWay(int x1, int y1, int x2, int y2) {
    return getClosest(y1,y2,elevators) + (int)(ceil(abs(x1-x2)/(double)v));
}

int stairWay(int x1, int y1, int x2, int y2) {
    return getClosest(y1,y2,stairs) + abs(x1-x2);
}

int query(int x1,int y1,int x2,int y2) {
    if (x1 == x2) {
        return abs(y1 - y2);
    }
    int e = elevatorWay(x1,y1,x2,y2);
    int s = stairWay(x1,y1,x2,y2);
    //cout << e << ' ' << s << '\n';
    return min(e,s);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("input.in","r",stdin);
    cin >> n >> m >> numElev >> numStairs >> v;
    for (int i = 0; i < numElev; i++) {
        int ci; cin >> ci;
        stairs.push_back(ci);
    }
    for (int i = 0; i < numStairs; i++) {
        int ci; cin >> ci;
        elevators.push_back(ci);
    }
    int q; cin >> q;
    while (q--) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << query(x1,y1,x2,y2) << '\n';
    }

    return 0;
}
	

