#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int s, n;
pair<int,int> A[1005];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        A[i] = {x,y};
    }

    sort(A,A+n);
    for (int i = 0; i < n; i++) {
        if (s > A[i].first) {
            s += A[i].second;
        }
        else {
            cout << "NO" << '\n';
            return 0;
        }
    }

    cout << "YES" << '\n';


    return 0;
}
	

