#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
int N, K;

const int maxn = 5005;

void madd(int& a, int b) {
    a = (a+b) % M;    
}

int ch[maxn][maxn];

int comb(int a, int b) { //# ways to distribute a things among b boxes
    return ch[a+b-1][b-1];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ch[0][0] = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 0; j <= i; j++) {
            ch[i][j] = ch[i-1][j];
            if (j-1 >= 0) madd(ch[i][j],ch[i-1][j-1]);
        }
    }
    cin >> N >> K;
    for (int i = 1; i <= K; i++) {
        int c1 = comb(K-i,i);
        int c2 = comb(N-K-(i-1),i+1);
        cout << ((1LL*c1*c2) % M) << '\n';
    }
}
