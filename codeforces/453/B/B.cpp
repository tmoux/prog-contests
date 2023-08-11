#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 105;
const int maxa = 59;
const int INF = 999999;
int A[maxn], n;
int dp[maxn][1 << 16];
int primepos[maxa], idx = 0;
int factors[maxa];

void checkPrime(int i) {
    if (i == 1) return;
    for (int j = 2; j*j <= i; j++) {
        if (i % j == 0) return;
    }
    primepos[i] = idx++;
}

int factor(int i) {
    int mask = 0;
    if (i == 1) return mask;
    for (int j = 2; j*j <= i; j++) {
        if (i % j == 0) {
            mask |= (1 << primepos[j]);
            while (i % j == 0) i /= j;
            mask |= factor(i);
            return mask;
        }
    }
    mask |= (1 << primepos[i]);
    return mask;
}

int f(int i, int mask) {
    if (dp[i][mask] >= 0) return dp[i][mask];
    if (i == n) return dp[i][mask] = 0;
    dp[i][mask] = INF;
    for (int j = 1; j < maxa; j++) {
        int pmask = factors[j];
        int dist = abs(A[i]-j);
        if (!(mask & pmask) && f(i+1,mask|pmask) + dist < dp[i][mask]) {
            dp[i][mask] = f(i+1,mask|pmask) + dist;
        }
    }
    return dp[i][mask];
}

void printSequence(int i, int mask, int numdiff) {
    //backtracking algorithm to find the sequence. If the known answer - dist = value of next state,
    //we know that we have a valid answer, so we can just print out our current j and continue on.
    if (i == n) return;
    for (int j = 1; j < maxa; j++) {
        int pmask = factors[j];
        int dist = abs(A[i]-j);
        if (!(mask & pmask) && f(i+1,mask|pmask) == numdiff - dist) {
            cout << j << ' ';
            printSequence(i+1,mask|pmask,numdiff-dist);
            return;
        }
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    memset(dp,-1,sizeof(dp));
    memset(primepos,-1,sizeof(primepos));
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 1; i < maxa; i++) {
        checkPrime(i);
        factors[i] = factor(i);
    }
    printSequence(0,0,f(0,0));

    return 0;
}
	

