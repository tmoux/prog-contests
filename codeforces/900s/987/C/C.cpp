#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 3005;
const int INF = 2000000005;
int n;
int least[maxn][4]; //gives least cost for i'th index, which is the j'th sign
int S[maxn], C[maxn];
int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> C[i];
    }
    for (int i = 0; i < n; i++) {
        least[i][1] = C[i];
    }
    for (int i = 0; i < n; i++) {
        least[i][2] = INF;
        for (int j = i + 1; j < n; j++) {
            if (S[i] < S[j]) {
                least[i][2] = min(least[i][2],least[j][1]); 
            }
        }
        if (least[i][2] != INF) {
            least[i][2] += C[i];
        }
        else {
            least[i][2] = -1;
        }
    }

    for (int i = 0; i < n; i++) {
        least[i][3] = INF;
        for (int j = i+1; j < n; j++) {
            if (S[i] < S[j] && least[j][2] != -1) {
                least[i][3] = min(least[i][3],least[j][2]);
            }
        }
        if (least[i][3] != INF) {
            least[i][3] += C[i];
        }
        else {
            least[i][3] = -1;
        }
        //cout << i << ' ' << least[i][3] << '\n';
    }
    //get answer
    int ans = INF;
    for (int i = 0; i < n; i++) {
        if (least[i][3] != -1) {
            ans = min(ans, least[i][3]);
        }
    }
    cout << (ans == INF ? -1 : ans) << '\n';
   /* 
    for (int i = 1; i <= 3; i++) {
        for (int j = 0; j < n; j++) {
            cout << least[j][i] << ' ';
        }
        cout << '\n';
    }
*/
    return 0;
}
	

