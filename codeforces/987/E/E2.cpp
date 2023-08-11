#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1000006;
int n, A[maxn]; 
int parent[maxn];

int minSwaps(int arr[], int n)
{
    bool visited[maxn];
    memset(visited,false,sizeof(visited));
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            int currIdx = i, currVal = arr[i];
            while (currVal != i) {
                ans++;
                currIdx = currVal;
                currVal = arr[currIdx];
                visited[currIdx] = true;
            } 
        }
    }
    return ans;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
   
    int numSwitch = minSwaps(A,n);
   
    //cout << numSwitch << '\n';
    bool a = (n & 1), b = (numSwitch & 1);
    cout << (a ^ b ? "Um_nik" : "Petr") << '\n';

    return 0;
}
	

