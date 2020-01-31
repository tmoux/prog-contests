#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    freopen("anniversary.in","r",stdin); freopen("anniversary.out","w",stdout);
    int w, h, ax, ay, bx, by; cin >> w >> h >> ax >> ay >> bx >> by;
    if (ay == by) {
        printf("%d %d %d %d\n",ax,0,bx,h);
    }
    else {
        printf("%d %d %d %d\n",0,ay,w,by);
    }
}

