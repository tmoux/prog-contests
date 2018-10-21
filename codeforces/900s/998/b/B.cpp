#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, B;
int A[maxn];
int odd = 0, even = 0;
vector<int> cuts;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> B;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    for (int i = 1; i < n; i++) {
        if (A[i] % 2 == 0) {
            even++;
        }
        else {
            odd++;
        }
        if (even == odd) {
            //valid cut
            cuts.push_back(abs(A[i]-A[i+1]));
        }
    }
    sort(cuts.begin(),cuts.end());
    int numcuts = 0;
    int total = 0;
    for (int i = 0; i < cuts.size(); i++) {
        total += cuts[i];
        if (total > B) {
            break;
        }
        else {
            numcuts++;
        }
    }
    cout << numcuts << '\n';


    return 0;
}
	

