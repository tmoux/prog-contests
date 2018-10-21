#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int i, m, q[1050];
char s[15];

int r(int n, int d) {
    for (int& w = q[n] = d + 1; n <= m && w < 11; w++) {
        if (w != q[n-1] && s[w-1]-'0' && r(n+1,w-d)) return 1;
    }
    return n > m;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    scanf("%s%d",&s,&m);
    cout << (r(1,0) ? "YES\n" : "NO");
    for (; q[m+1] && i < m; printf("%d ",q[++i]));

    return 0;
}
	

