#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int B[maxn];
int n;
int dx[] = {-1,0,1};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }
    if (n == 1 || n == 2) {
        cout << "0\n";
        return 0;
    }
    int minAns = 2000000;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int numChange = abs(dx[i]) + abs(dx[j]);
            int Bp[maxn];
            Bp[0] = B[0] + dx[i];
            Bp[1] = B[1] + dx[j];
            int expected = Bp[1] - Bp[0];
            for (int i = 2; i < n; i++) {
                Bp[i] = Bp[i-1] + expected;
                if (abs(Bp[i]-B[i]) > 1) {
                    numChange = 2000000;
                    break;
                }
                else {
                    numChange += abs(Bp[i]-B[i]);
                }
            }
            minAns = min(minAns,numChange);
        }
    }
    if (minAns == 2000000) {
        cout << "-1\n";
    }
    else {
        cout << minAns << '\n';
    }
    


    return 0;
}
	

