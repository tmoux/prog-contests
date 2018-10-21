#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b, x; cin >> a >> b >> x;
    int curr = 0;
    if (b > a) curr = 1;
    int tot = a + b;
    int numBlocks = x + 1;
    int coun[2] = {a,b};
    
    for (int i = 0; i < numBlocks-2; i++) {
        cout << curr;
        coun[curr]--;
        curr = !curr;
    }
    for (int i = 0; i < coun[curr]; i++) {
        cout << curr;
    }
    curr = !curr;
    for (int i = 0; i < coun[curr]; i++) {
        cout << curr;
    }



    return 0;
}
	

