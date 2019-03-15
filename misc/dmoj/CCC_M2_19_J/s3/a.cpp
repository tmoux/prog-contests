#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using int128 = __int128;

const int maxn = 3005;
int N;

int128 ch3(int128 x) {return x*(x-1)*(x-2)/6;}
int128 ch2(int128 x) {return x*(x-1)/2;}
void reduce(pair<int128,int128>& p) {
    int128 gc = __gcd(p.first,p.second);
    p.first /= gc;
    p.second /= gc;
}

struct Vec
{
    pair<int128,int128> m, b;
    Vec(ll x1, ll y1, ll x2, ll y2) {
        int128 num = y2-y1;
        int128 den = x2-x1;
        if (den == 0) {
            
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; i++) {

    }
}

