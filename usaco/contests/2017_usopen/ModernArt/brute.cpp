#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int N, A[maxn][maxn];

void amin(int& a, int b) {
	a = min(a,b);
}
void amax(int& a, int b) {
	a = max(a,b);
}

int mnX[maxn*maxn], mxX[maxn*maxn], mnY[maxn*maxn], mxY[maxn*maxn];

bool na[maxn*maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    //max time with cin: 765 ms
    //max time with scanf/printf: 767 ms
    freopen("art.in","r",stdin); freopen("art.out","w",stdout);
    scanf("%d",&N);
    for (int i = 0; i <= N*N; i++) {
    	mnX[i] = N;
    	mnY[i] = N;
    }
    for (int i = 0; i < N; i++) {
    	for (int j = 0; j < N; j++) {
    		scanf("%d",&A[i][j]);
    	}
    }
    for (int i = 0; i < N; i++) {
    	for (int j = 0; j < N; j++) {
    		amin(mnX[A[i][j]],j);
    		amin(mnY[A[i][j]],i);
    		amax(mxX[A[i][j]],j);
    		amax(mxY[A[i][j]],i);
    	}
    }
    
    int cnt = 0;
    for (int i = 1; i <= N*N; i++) {
    	if (mnY[i] != N && mnX[i] != N) {
    		cnt++;
    		for (int x = mnX[i]; x <= mxX[i]; x++) {
    			for (int y = mnY[i]; y <= mxY[i]; y++) {
    				if (A[y][x] != i) {
    					na[A[y][x]] = true;
    				}
    			}
    		}
    	}
    }
    

    //output
    int ans = 0;
    for (int i = 1; i <= N*N; i++) {
    	if (!na[i]) ans++;
    }
    printf("%d\n",cnt==1?N*N-1:ans);

    return 0;
}

