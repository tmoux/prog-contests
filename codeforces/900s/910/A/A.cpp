#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
pair<bool,int> A[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, d;    
    cin >> n >> d;
    string s; cin >> s;
    A[0] = {true,0};
    for (int i = 1; i < n; i++) {
        if (s[i] == '1') {
            A[i].first = true;
            bool found = false;
            for (int j = max(0,i-d); j < i; j++) {
                if (A[j].first) {
                    found = true;
                    A[i].second = A[j].second+1;
                    break;
                }
            }
            if (!found) {
                cout << -1 << '\n';
                return 0;
            }
        }
    }
   
    cout << (A[n-1].second == 0 ? -1 : A[n-1].second) << '\n';

    return 0;
}
	

