#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int A[100], n;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    if (A[n-1] == 0) {
        cout << "UP\n";
        return 0;
    }
    else if (A[n-1] == 15) {
        cout << "DOWN\n";
        return 0;
    }
    if (n == 1) {
        cout << -1 << '\n';
        return 0;
    }
    bool increasing = (A[n-1] - A[n-2]) > 0;
    cout << (increasing ? "UP" : "DOWN") << '\n';
    return 0;
}
	

