#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

vector<int> A;
int arr[55];
bool seen[1005];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = n-1; i >= 0; i--) {
        int ai = arr[i];
        if (!seen[ai]) {
            A.push_back(ai);
            seen[ai] = true;
        }
    }
    cout << A.size() << '\n';\
    reverse(A.begin(),A.end());
    for (int i: A) {
        cout << i << ' ';
    }



    return 0;
}
	

