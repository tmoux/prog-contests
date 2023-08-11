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
    int n, m; cin >> n >> m;
    int curr = 1;
    for (int i = 0; i < n; i++) {
        cout << curr;
        curr = !curr;
    }


    return 0;
}
	

