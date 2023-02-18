#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6, maxk = 20;

struct Node
{
    Node* par[maxk];
    char c;
    int len;
    Node(char cc = '#', Node *p = NULL) {
        c = cc;
        par[0] = p;
        len = p == NULL ? 0 : p->len + 1;
        for (int k = 1; k < maxk; k++) {
            if (par[k-1] == NULL) break;
            par[k] = par[k-1]->par[k-1];
        }
    }
};

string s(Node *test) {
    string s;
    while (test != NULL) {
        s = s + test->c;
        test = test->par[0];
    }
    reverse(s.begin(),s.end());
    return s;
}

Node* nodes[maxn];
int q;

void Init() {
    q = 0;
    nodes[q++] = new Node();
}

void TypeLetter(char L) {
    nodes[q] = new Node(L,nodes[q-1]);
    q++;
    //cout << q << ": " << s(nodes[q-1]) << '\n';
}

void UndoCommands(int U) {
    nodes[q] = nodes[q-U-1];
    q++;
    //cout << q << ": " << s(nodes[q-1]) << '\n';
}

char GetLetter(int P) {
    Node *curr = nodes[q-1];
    P = curr->len - 1 - P;
    for (int k = maxk-1; k >= 0; k--) {
        if (1<<k <= P) {
            P -= 1<<k;
            curr = curr->par[k];
        }
    }
    //cout << s(nodes[q-1]) << '\n';
    return curr->c;
}

/*
int main()
{
    Init();
    TypeLetter('a');
    TypeLetter('b');
    cout << GetLetter(1) << '\n';
    TypeLetter('d');
    UndoCommands(2);
    UndoCommands(1);
    cout << GetLetter(2) << '\n';
    TypeLetter('e');
    UndoCommands(1);
    UndoCommands(5);
    TypeLetter('c');
    cout << GetLetter(2) << '\n';
    UndoCommands(2);
    cout << GetLetter(2) << '\n';
}
*/
