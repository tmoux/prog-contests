#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

bool A[105];
int n;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int ans = 0;
    int mode = 0; //0 is at home, 1 is at school
    for (int i = 0; i < n; i++) {
        if (mode == 0) {
            if (A[i]) {
                mode = 1;
                ans++;
            }
        }
        else {
            if (A[i] || A[i+1]) {
                ans++;
            }
            else {
                mode = 0;
            }
        }
    }
    cout << ans << '\n';


    return 0;
}
	

