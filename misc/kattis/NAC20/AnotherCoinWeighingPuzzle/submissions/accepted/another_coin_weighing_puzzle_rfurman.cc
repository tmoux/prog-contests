
#include <iostream>
#include <string>
#include <vector>

using namespace std;

long MOD=998244353;

int mu[2010000];

long long powmod(long b, long k) {
    if(k==0) return 1;
    if(k==1) return b%MOD;
    long long ret = powmod(b, k/2);
    ret = (ret * ret)%MOD;
    if(k%2) ret = (ret * b)%MOD;
    return ret;
}


// (2K+1)^M +- (2K/d+1)^M ...

int main(void) {
    mu[1]=1;
    int M,K; cin >> M >> K;
    for(int n=2; n<=K; n++) {
        bool prime=true;
        for(int d=2; d*d<=n; d++) if(n%d==0) {
            if(n%(d*d)==0) mu[n]=0;
            else mu[n]=-mu[n/d];
            prime=false;
            break;
        }
        if(prime) mu[n]=-1;
    }
    long long ret = 1;
    for(int d=1; d<=K; d++) {
        ret += mu[d] * (powmod(2*(K/d)+1, M) - 1);
        ret = ((ret%MOD)+MOD)%MOD;
    }
    cout << ret << endl;

}
