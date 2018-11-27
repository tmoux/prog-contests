#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


bool isPrime(int x) {
    if (x == 1) return false;
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

vector<char> vowels = {'a','e','i','o','u'};
int countVowels(string& s) {
    int cnt = 0;
    for (char c: s) {
        auto it = find(vowels.begin(),vowels.end(),c);
        if (it != vowels.end()) cnt+=2;
        else if (c == 'y') cnt++;
    }
    return cnt;
}

bool isSquare(int x) {
    int r = (int)(sqrt(x));
    for (int i = max(0,r-2); i <= r+3; i++) {
        if (i*i==x) return true;
    }
    return false;
}

bool sqstring(string& s) {
    int r = countVowels(s);
    if (r % 2 != 0) return false;
    r /= 2;
    return isSquare(s.size()) && isSquare(r);
}

bool valid(string s) {
    int r = countVowels(s);
    if (r % 2 != 0) return false;
    r /= 2;
    return (isPrime(s.size()) && r % 2 == 1) || sqstring(s);
}

int main()
{
    int t; scanf("%d\n",&t);
    for (int i = 1; i <= t; i++) {
        int n;
        scanf("%d\n",&n);
        //cout << "n = " << n << '\n';
        vector<string> ans;
        string s;
        while (n--) {
            getline(cin,s);
            //cout << s << '\n';
            if (valid(s)) ans.emplace_back(s);
        }
        printf("Practice #%d: ",i);
        if (ans.empty()) {
            printf("It's hopeless!\n\n");

        }
        else {
            printf("%d valid options\n",ans.size());
            for (string t: ans) {
                printf("%s\n",t.c_str());
            }
            printf("\n");
        }
    }

    return 0;
}

