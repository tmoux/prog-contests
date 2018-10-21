#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, t;
char s1[maxn], s2[maxn], a[maxn];
int pairs[maxn];

char diff(char c) {
    char res = 'a';
    while (res == c) res++;
    return res; 
}
char diff(char c, char d) {
    char res = 'a';
    while (res == c || res == d) res++;
    return res;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(pairs,-1,sizeof(pairs));
    scanf("%d %d\n",&n,&t);
    scanf("%s\n%s\n",s1,s2);
    pair<int,int> curr = {-1,-1};
    int d = 0;
    for (int i = 0; i < n; i++) {
        if (s1[i] == s2[i]) {
            a[i] = s1[i];
        }
        else {
            if (curr.first == -1) {
                //start of a new pair
                d++;
                curr.first = i;
                a[i] = diff(s1[i],s2[i]);
            }
            else {
                curr.second = i;
                pairs[curr.first] = curr.second;
                a[curr.first] = s1[curr.first];
                a[curr.second] = s2[curr.second];
                curr = {-1,-1};
            }
        }
    }

    if (t < d) {
        //impossible
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < n && d < t; i++) {
        if (s1[i] == s2[i]) {
            d++;
            a[i] = diff(s1[i],s2[i]);
        }
        else if (pairs[i] != -1) {
            d++;
            a[i] = diff(s1[i],s2[i]);
            a[pairs[i]] = diff(s1[pairs[i]],s2[pairs[i]]);
        }
    }
    cout << a << '\n';
    


    return 0;
}
	

