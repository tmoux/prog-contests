#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n;
int degree[maxn];
int degSet[maxn];
vector<pair<int,int>> edges;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> degSet[i];
    }
    int numVertices = degSet[n-1];
    int* ptr = degree+n-1;
    for (int i = 0; i < n; i++) {
        int num
    }

    return 0;
}
	

