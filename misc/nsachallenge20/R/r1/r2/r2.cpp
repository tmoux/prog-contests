#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//screw this problem lol
map<char,string> ToInstruction =
{
    {'3',"Add"},
    {'4',"Subt"},
    {'b',"AddI"},
    {'a',"Clear"},
    {'1',"Load"},
    {'2',"Store"},
    {'5',"Input"},
    {'6',"Output"},
    {'9',"Jump"},
    {'8',"Skipcond"},
    {'0',"JnS"},
    {'c',"JumpI"},
    {'e',"StoreI"}, //storeI, loadI are swapped?
    {'d',"LoadI"},
    {'7',"Halt"}
};

set<string> args = {
    "Add",
    "Subt",
    "AddI",
    "Load",
    "Store",
    "Jump",
    "Skipcond",
    "JnS",
    "JumpI",
    "StoreI",
    "LoadI"
};

char hx(int x) {
    if (x < 10) return '0'+x;
    return (x-10)+'a';
}

int xh(char c) {
    if ('0' <= c && c <= '9') return c-'0';
    return c-'a'+10;
}

int toInt(string s) {
    int res = 0;
    assert(s.size() == 3); 
    int mult = 1;
    for (int i = 2; i >= 0; i--) {
        res += mult*xh(s[i]);
        mult *= 16;
    }
    return res;
}

string toHex(int x) {
    string ret = "";    
    while (x > 0) {
        ret = ret + hx(x%16);
        x /= 16;
    }
    while (ret.size() < 3) {
        ret = '0' + ret;
    }
    return ret;
}

struct Instr {
    string instr;
    int operand;
    int id;
};

const int maxn = 5005;
vector<Instr> v;

pair<string,string> tab[maxn]; //from, val
int ac = 5000;
string format(pair<string,string> p) {
    if (p.first.empty()) return p.second;
    return "<FROM " + p.first + ": " + p.second + ">";
}

int main() {
    string s;
    bool done = false;
    int cnt = 0;
    while (cin >> s) {
        string instr = ToInstruction[s[0]];
        int operand = toInt(s.substr(1));
        string code = toHex(cnt);
        cout << toHex(cnt) << ": " << instr;
        if (args.count(instr)) cout << " " << s.substr(1);
        cout << '\n';
        if (instr == "Clear") {
            tab[ac] = {"","0x0\n"};
            cout << " --> AC=" << format(tab[ac]);
        }
        else if (instr == "Input") {
            tab[ac] = {code,"Input"};
            cout << "  --> AC=" << format(tab[ac]) << '\n';
        }
        else if (instr == "Store") {
            cout << "  <-- AC=" << format(tab[ac]) << '\n';
            tab[operand] = tab[ac];
            cout << "  --> Cell[" << s.substr(1) << "]=" << format(tab[operand]) << '\n';
        }
        else if (instr == "Add") {
            cout << "  <-- AC=" << format(tab[ac]) << '\n';
            cout << "  <-- Cell[" << s.substr(1) << "]" << format(tab[operand]) << '\n';
            tab[ac] = make_pair(code,"Add "+s.substr(1));
            cout << "  --> AC=" << format(tab[ac]) << endl;
        }
        else if (instr == "Output") {
            cout << "  <-- AC=" << format(tab[ac]) << '\n';
        }
        else if (instr == "Halt") {
            break;
        }
        cnt++;
    }
}
