#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<int,double> mp[105];

class BeatTheStar
{
    public:
    double doesItMatter(int N, int G) {
        int mx = N*(N+1)/2;
        mp[0][0] = 1.0;
        for (int i = 1; i <= N; i++) {
            for (int k = -mx; k <= mx; k++) {
                if (i != G) {
                    mp[i][k] = 0.5*mp[i-1][k-i] + 
                               0.5*mp[i-1][k+i];
                }
                else {
                    mp[i][k] = mp[i-1][k-i];
                }
                //printf("[%d][%d]: %.4f\n",i,k,mp[i][k]);
            }
        }
        double ans = 0.0;
        for (int k = 1; k <= 2*G; k++) {
            ans += mp[N][k];
        }
        return ans;
    }
};

int main() {
    BeatTheStar t;
    int N, G; cin >> N >> G;
    cout << t.doesItMatter(N,G) << endl;
}

