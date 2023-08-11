#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node
{
    Node* arr[26];
    bool used;
    Node() {
        for (int i = 0; i < 26; i++) arr[i] = NULL;
        used = false;
    }
};

bool good[26];
int ans = 0;
int k;

void insert(Node *curr, string s) {
    int numBad = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (!good[s[i]-'a']) numBad++;
        if (numBad > k) return;
        int nx = s[i]-'a';
        if (curr->arr[nx] == NULL) curr->arr[nx] = new Node();
        curr = curr->arr[nx];
        if (!curr->used) {
            ans++;
            curr->used = true;    
            //cout << s.substr(0,i+1) << '\n';
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    for (int i = 0; i < 26; i++) {
        char c; cin >> c;
        good[i] = c == '1';
    }
    cin >> k;
    Node *root = new Node();
    for (int i = 0; i < (int)s.size(); i++) {
        insert(root,s.substr(i));    
    }
    cout << ans << '\n';

    return 0;
}

