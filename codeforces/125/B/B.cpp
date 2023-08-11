#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stack>
using namespace std;
typedef long long ll;



int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    stack<char> st;
    string s; cin >> s;
    bool isEsc = false;
    for (char c: s) {
        if (c == '<' || c == '>') continue;
        if (c == '/') isEsc = true;
        else {
            if (!isEsc) {
                int space = 2*st.size();
                st.push(c);
                for (int i = 0; i < space; i++) {
                    cout << ' ';
                }
                cout << '<' << c << ">\n";
            }
            else {
                isEsc = false;
                st.pop();
                int space = 2*st.size();
                for (int i = 0; i < space; i++) {
                    cout << ' ';
                }
                cout << "</" << c << ">\n";
            }
        }
    }


    return 0;
}

