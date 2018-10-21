#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
bool iscomp[maxn];
void sieve() {
    for (int i = 2; i < maxn; i++) {
        if (!iscomp[i]) {
            for (int j = i + i; j < maxn; j += i) {
                iscomp[j] = true;
            }
        }
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    sieve();
    int prev = -1;
    int ans = 0;
    for (int i = 2; i < n; i++) {
        if (!iscomp[i]) {
            if (prev == -1) {
                prev = i;
            }
            else {
                int s = prev + i + 1;
                if (s > n) break;
                if (!iscomp[s]) ans++;
                prev = i;
            }
        }
    }
    cout << (ans >= k ? "YES" : "NO") << '\n';


    return 0;
}
	

