#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//why does topcoder have such SHIT problems lol

const int maxn = 605;
const int MOD = 1e9+7;
int dp[2][maxn][maxn][2];

int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = (1LL*res*a) % MOD;
        a = (1LL*a*a) % MOD;
        b >>= 1;
    }
    return res;
}

int inverse(int x) {
    return modexp(x,M-2);
}

int mult(int a, int b) {
    return (1LL*a*b) % MOD;
}

class HockeyPlayoff {
public:
    int winProbability(int winsNeeded, int AwinHome, int BwinHome) {
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i <= winsNeeded; i++) {
                for (int streak = 0; streak <= 20; streak++) {
                    for (int whose = 0; whose <= 1; whose++) {
                        dp[k&1][i][streak][whose] = modexp(100,windNeeded*2-1);    
                    }
                }
            }
        }
        for (int k = 0; k < 2*winsNeeded-1; k++) {
            for (int i = 0; i <= winsNeeded; i++) {
                for (int streak = 0; streak <= 20; streak++) {
                    for (int whose = 0; whose <= 1; whose++) {
                        int turn = (k/2) % 2;
                        int pct = turn == 0 ? aWinHome : 100-bWinHome;
                        if (whose == 0) {
                            pct = min(100,pct+5*streak);
                        }
                        else {
                            pct = max(0,pct-5*streak);
                        }
                        dp[(k&1)^1][]
                    }
                }
            }
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);


}

