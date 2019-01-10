#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 103, M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    while (a > M) a -= M;
}

struct Matrix
{
    int m[maxn][maxn];
    int n;
    Matrix(int N_) {
        n = N_;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                m[i][j] = 0;
            }
        }
    }
};

Matrix operator*(Matrix a, Matrix b) {
    int n = a.n;
    Matrix res(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                madd(res.m[i][j],(1LL*a.m[i][k]*b.m[k][j])%M);
            }
        }
    }
    return res;
}

Matrix power(Matrix a, ll p) {
    int n = a.n;
    Matrix ans(a.n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans.m[i][j] = (i==j);
        }
    }
    while (p) {
        if (p & 1) ans = ans * a;
        a = a * a;
        p >>= 1;
    }
    return ans;
}

map<string,int> mp;
int counter = 0;
int N;
pair<string,int> program[maxn]; //0 = var declaration, 1 = start loop, 2 = end loop, 3 = RETURN
int getType(const string& s) {
    stringstream ss(s);
    string firstWord;
    ss >> firstWord;
    if (firstWord == "RETURN") return 3;
    if (firstWord == "}") return 2;
    if ('0' <= firstWord[0] && firstWord[0] <= '9') return 1;
    else {
        if (!mp.count(firstWord)) mp[firstWord] = counter++; 
        return 0;
    }
}

vector<int> apply(Matrix a, const vector<int>& vals) {
    vector<int> res(N,0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            madd(res[i],(1LL*a.m[i][j]*vals[j])%M);    
        }
    }
    return res;
}

int getPowerFromLoop(int line) {
    assert(program[line].second == 1);
    stringstream ss(program[line].first);
    int res; ss >> res;
    return res;
}

bool is_num(const string& s) {
    return !s.empty() && s.find_first_not_of("0123456789") == string::npos;
}

Matrix getMatrixFromStatement(int line) {
    Matrix res(N);
    for (int i = 0; i < N; i++) {
        res.m[i][i] = 1;    
    }
    stringstream ss(program[line].first);
    string s; ss >> s;
    int add = mp[s];
    es.m[add][add] = 0;
    while (ss >> s) {
        if (is_num(s)) {
            int num; 
            istringstream(s) >> num;
            madd(res.m[add][N-1],num);
        }
        else if (mp.count(s)) {
            madd(res.m[add][mp[s]],1);
        }
    }
    return res;
}

Matrix getMatrixFromLoop(int line) {
    int depth = 1;
    Matrix res(N);
    for (int i = 0; i < N; i++) res.m[i][i] = 1;
    int k = getPowerFromLoop(line);
    for (int i = line + 1; ; i++) {
        if (program[i].second == 0) {
            if (depth == 1) {
                res = getMatrixFromStatement(i) * res;
            }
        }
        else if (program[i].second == 1) {
            if (depth == 1) {
                res = getMatrixFromLoop(i) * res;
            }
            depth++;    
        }
        else {
            depth--;
            if (depth == 0) break;        
        }
    }
    res = power(res,k);
    return res;
}

void output(vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << i << ": " << v[i] << '\n';
    }
}

int main()
{
    freopen("cowbasic.in","r",stdin); freopen("cowbasic.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s;
    int i = 0;
    vector<int> blocks;
    int currDepth = 0;
    string returnval;
    while (getline(cin,s)) {
        program[i].first = s;
        program[i].second = getType(s);
        if (currDepth == 0) {
            if (program[i].second != 3) blocks.push_back(i);
            else {
                stringstream w(program[i].first);
                string ss;
                w >> ss >> ss;
                returnval = ss;
            }
        }
        if (program[i].second == 1) currDepth++;
        if (program[i].second == 2) currDepth--;
        i++;
    }
                            
    N = counter + 1;
    vector<int> vals(N,0);
    vals[N-1] = 1;
    for (int j: blocks) {
        Matrix mult(N);
        if (program[j].second == 1) mult = getMatrixFromLoop(j);
        else {
            mult = getMatrixFromStatement(j);    
            
        }
        vals = apply(mult,vals);    
    }
    cout << vals[mp[returnval]] << '\n';
    return 0;
}
