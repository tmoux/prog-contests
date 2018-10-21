#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n;
bool isSub(string a, string b) {
    return (a.find(b) != string::npos); 
    //if b is a substring of a
}


int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < n; i++) {
        string ms = s[i]; int idx = i;
        for (int j = i+1; j < n; j++) {
            if (isSub(ms,s[j])) {
                ms = s[j];
                idx = j;
            }
            else if (!isSub(s[j],ms)) {
                cout << "NO\n";
                return 0;
            }
        }
        string tmp = s[i];
        s[i] = ms;
        s[idx] = tmp;
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        cout << s[i] << '\n';
    }



    return 0;
}
	

