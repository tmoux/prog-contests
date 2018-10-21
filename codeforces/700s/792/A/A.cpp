#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int n, A[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(A,A+n);
    int mindist = -1, num = 0;
    for (int i = 0; i < n - 1; i++) {
        int dist = A[i+1] - A[i];
        if (mindist == -1 || dist < mindist) {
            mindist = dist;
            num = 1;
        }
        else if (dist == mindist) {
            num++;   
        }
    }
    cout << mindist << ' ' << num << '\n';


    return 0;
}
	

