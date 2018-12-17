#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N;
ll f[maxn];
double ans[maxn];

double prob(int i, int j) {
    if (i > j) return prob(N-i+1,N-j+1);
    return (double)(i)/j;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("balance.in","r",stdin); freopen("balance.out","w",stdout);
    cin >> N;
    f[0] = 0; f[N+1] = 0;
    for (int i = 1; i <= N; i++) {
        cin >> f[i];
        ans[i] = f[i];
    }
    for (int i = 1; i <= N; i++) {
        ll p = f[i];
        for (int j = i-1; j >= 1; j--) {
            double p1 = p*prob(j,i);
            ans[j] = max(ans[j],p1);
            //cout << i << ' ' << j << ' ' << (double)(j)/i << '\n';
        }
        for (int j = i+1; j <= N; j++) {
            //cout << i << ' ' << j << ' ' << ((N-j+1)/(double(N-i+1))) << '\n';
            double p1 = p*prob(j,i);
            ans[j] = max(ans[j],p1);
        }
    }

    for (int i = 1; i <= N; i++) {
        ll a = (ll)(ans[i]*100000.0);
        double b = max((double)f[i],0.5*(ans[i-1]+ans[i+1]));
        ll c = (ll)(b*100000.0);
        cout << a << ' ' << c << ": delta = " << (a-c)/(double)(100000) << '\n';
        //cout << (a-c) << '\n';
        //assert(a-c == 0);
    }
    
    return 0;
}

