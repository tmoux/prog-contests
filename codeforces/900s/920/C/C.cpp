#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int n;
bool poss[maxn];
int A[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    string s; cin >> s;
    for (int i = 1; i < n; i++) {
        poss[i] = s[i-1] == '1';
    }

    int start = 1, end;
    int mode = 0;
    set<int> nums;
    for (int i = 1; i <= n; i++) {
        if (poss[i]) {
            if (mode == 0) {
                nums = {A[i]};
                start = i;
                mode = 1;
            }
            else {
                nums.insert(A[i]);
            }
        }
        else {
            if (mode == 0) {
                if (A[i] != i) {
                    cout << "NO\n";
                    return 0;
                }
            }
            else {
                mode = 0;
                nums.insert(A[i]);
                end = i;
                
                if (*nums.begin() != start || *nums.rbegin() != end) {
                    cout << "NO\n";
                    return 0;
                }
            }
        }
    }
    cout << "YES\n";
    return 0;
}
	

