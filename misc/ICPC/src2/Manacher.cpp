#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

//you need twice the length of original string here, since you need space for adding $
const int maxn = 2100000;

char str[maxn], str2[maxn];
//p[i] is just "how long you can extend from i in both ways"
int p[maxn];

void manacher(int n)
{
    int mx = 0;
    int id = 0;
    for (int i = 1;i <= n;++i){
        if (mx >= i){
            p[i] = min(mx - i, p[2 * id - i]);
        }
        else{
            p[i] = 0;
        }
        for (;str[i + p[i] + 1] == str[i - p[i] - 1];){
            p[i]++;
        }
        if (p[i] + i > mx){
            id = i;
            mx = p[i] + i;
        }
    }
}
