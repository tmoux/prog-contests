#include <iostream>
#include <math.h>
using namespace std;

int main() 
{
    int k, n, s, p;
    cin >> k >> n >> s >> p;
    int sheetsPP = (int)(ceil((double)n/s));
    int totalSheets = sheetsPP*k;
    //cout << sheetsPP << ' ' << totalSheets << '\n';
    int ans = (int)(ceil((double)totalSheets/p));
    cout << ans << '\n';
}
