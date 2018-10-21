#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    int x, y, z, t1, t2, t3; scanf("%d %d %d %d %d %d",&x,&y,&z,&t1,&t2,&t3);
    int stairs = abs(x-y) * t1;
    int elevator = (abs(z-x)+abs(x-y))*t2 + 3*t3;
    printf("%s\n",elevator <= stairs ? "YES" : "NO");
    return 0;
}

