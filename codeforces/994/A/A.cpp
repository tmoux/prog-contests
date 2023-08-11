#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int pressed[10];
bool seen[10];
int n, m;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> pressed[i];
    }
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        seen[x] = true;
    }
    for (int i = 0; i < n; i++) {
        if (seen[pressed[i]]) {
            cout << pressed[i] << ' ';
        }
    }


    return 0;
}
	

