#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const double p[4][4] = {
    {.25,.25,.25,.25},
    {.5,.5,0,0},
    {.5,0,.5,0},
    {1,0,0,0}
};

int pc(int x) {
    return __builtin_popcount(x);
}

random_device device;
mt19937 gen(device());

int next(int x) {
    int r = gen() % 4;
    if (x == 0) {
        return r;
    }
    else if (x == 1) {
        if (r < 2) return 0;
        else return 1;
    }
    else if (x == 2) {
        if (r < 2) return 0;
        else return 2;
    }
    else return 0;
}

int walk(int k) {
    int x = gen() % 4;
    int ans = pc(x);
    for (int i = 0; i < k-1; i++) {
        x = next(x);
        ans += pc(x);
    }
    return ans;
}

double sample(int k) {
    const int N = 100000;
    int tot = 0;
    for (int _ = 0; _ < N; _++) {
        tot += walk(k);
    }
    return (double)tot/N;
}

int main() {
    int n; cin >> n;
    double dp[n+1][4];
    double prob[n+1][4];
    memset(dp,0,sizeof dp);
    memset(prob,0,sizeof prob);
    prob[0][0] = prob[0][1] = prob[0][2] = prob[0][3] = 0.25;
    dp[0][0] = 0;
    dp[0][1] = 0.25;
    dp[0][2] = 0.25;
    dp[0][3] = 0.5;
    double psum = 0;
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < 4; j++) {
            sum += dp[i][j];
            //printf("[%d][%d]: %f\n",i,j,dp[i][j]);
            printf("p [%d][%d]: %f\n",i,j,prob[i][j]);
            for (int k = 0; k < 4; k++) {
                prob[i+1][k] += prob[i][j]*p[j][k];
            }
        }
        for (int k = 0; k < 4; k++) {
            dp[i+1][k] = prob[i+1][k]*pc(k);
        }
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                dp[i+1][k] += p[j][k]*dp[i][j];
            }
        }
        cout << i << ": " << sum << ' ' << (sum-psum) << '\n';
        psum = sum;
        //cout << i << ": " << sum << ": " << sample(i+1) << '\n';
    }
}
