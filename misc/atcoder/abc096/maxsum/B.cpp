#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int K;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int maxnum = 0;
    int currsum = 0;
    for (int i = 0; i < 3; i++) {
        int a; cin >> a;
        maxnum = max(maxnum,a);
        currsum += a;
    }
    currsum -= maxnum;
    cin >> K;
    currsum += maxnum * (1 << K);
    cout << currsum << '\n';



    return 0;
}
	

