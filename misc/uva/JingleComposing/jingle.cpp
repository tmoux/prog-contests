#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
using namespace std;
typedef long long ll;

unordered_map<char,int> mp {{'W',64},{'H',32},{'Q',16},{'E',8},{'S',4},{'T',2},{'X',1}};

bool isValid(const string& s) {
    int sum = 0;
    for (char c: s) {
        sum += mp[c];
    }
    return sum == 64;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    while (true) {
       string s; cin >> s;
       if (s == "*") break;
       vector<string> res;
       string token;
       istringstream tokenStream(s.substr(1));
       while (getline(tokenStream, token,'/')) {
           res.push_back(token);
       }
       int ans = 0;
       for (string f: res) {
           ans += isValid(f);
       }
       cout << ans << '\n';
    }

    return 0;
}
	

