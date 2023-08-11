#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    set<int> s;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if (ai != 0) {
            s.insert(ai);
        }
    }
    cout << s.size() << '\n';


    return 0;
}
	

