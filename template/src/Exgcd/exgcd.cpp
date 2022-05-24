#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<int,pair<int,int>> gcd(int a, int b) {
    if (a == 0) return {b,{0,1}};
    if (b == 0) return {a,{1,0}};
    int x1 = 1, x2 = 0, y1 = 0, y2 = 1;
    while (a && b) {
        int r = a/b;
        int tmp = b;
        b = a - r * b;
        a = tmp;
        int tmpx = x2, tmpy = y2;
        x2 = x1 - r * x2;
        y2 = y1 - r * y2;
        x1 = tmpx, y1 = tmpy;
        //printf("%d: %d, %d\n",b,x2,y2);
    }
    return {a,{x1,y1}};
}

int mod_inverse(int x, int n) { //must check that x and n are coprime!!!
    auto ans = gcd(x,n);
    while (ans.second.first < 0) ans.second.first += n;
    return ans.second.first;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b; cin >> a >> b;
    cout << mod_inverse(a,b) << '\n';

    return 0;
}

