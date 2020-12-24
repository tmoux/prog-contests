#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 10, SZ = 12;
const int M = (N-2)*SZ;

struct BigPiece {
  char grid[M][M], grid2[M][M];
  void rotate() {
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < M; j++) {
        grid2[j][M-1-i] = grid[i][j];
      }
    }
    swap(grid,grid2);
  }

  void flipH() {
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < M; j++) {
        grid2[M-1-i][j] = grid[i][j];
      }
    }
    swap(grid,grid2);
  }

  int cnt(string monster[3]) {
    int ans = 0;
    for (int i = 0; i + 3 <= M; i++) {
      for (int j = 0; j + 20 <= M; j++) {
        bool poss = true;
        for (int ii = 0; ii < 3; ii++) {
          for (int jj = 0; jj < 20; jj++) {
            if (monster[ii][jj] == ' ') continue;
            if (grid[i+ii][j+jj] != monster[ii][jj]) {
              poss = false;
              break;
            }
          }
        }
        if (poss) ans++;
      }
    }
    return ans;
  }

  int total() {
    int ans = 0;
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < M; j++) {
        ans += grid[i][j] == '#';
      }
    }
    return ans;
  }
};

struct Piece {
  int id;
  char grid[N][N], grid2[N][N];

  void rotate() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        grid2[j][N-1-i] = grid[i][j];
      }
    }
    swap(grid,grid2);
  }

  void flipH() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        grid2[N-1-i][j] = grid[i][j];
      }
    }
    swap(grid,grid2);
  }

  void flipV() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        grid2[i][N-1-j] = grid[i][j];
      }
    }
    swap(grid,grid2);
  }

  void print() {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cout << grid[i][j];
      }
      cout << '\n';
    }
  }
};

Piece pieces[SZ*SZ];
bool used[SZ*SZ];
Piece board[SZ][SZ];

bool fits(Piece p, int i, int j) {
  if (i > 0) {
    for (int k = 0; k < N; k++) {
      if (p.grid[0][k] != board[i-1][j].grid[N-1][k]) {
        return false;
      }
    }
  }
  if (j > 0) {
    for (int k = 0; k < N; k++) {
      if (p.grid[k][0] != board[i][j-1].grid[k][N-1]) {
        return false;
      }
    }
  }
  return true;
}

bool done = false;
void go(int i, int j) {
  if (done) return;
  cout << i << ' ' << j << '\n';
  if (i == SZ) {
    //found answer
    ll ans = 1LL*board[0][0].id*board[0][SZ-1].id*board[SZ-1][0].id*board[SZ-1][SZ-1].id;
    for (int a = 0; a < SZ; a++) {
      for (int b = 0; b < SZ; b++) {
        cout << board[a][b].id << ' ';
      }
      cout << '\n';
    }
    cout << ans << '\n';
    done = true;
    return;
  }
  int ni, nj;
  if (j == SZ-1) {
    ni = i+1;
    nj = 0;
  }
  else {
    ni = i;
    nj = j+1;
  }
  for (int q = 0; q < SZ*SZ; q++) {
    if (used[q]) continue;
    used[q] = true;
    for (int k = 0; k < 4; k++) {
      for (int _: {0,1}) {
        if (fits(pieces[q],i,j)) {
          board[i][j] = pieces[q];
          go(ni,nj);
          if (done) return;
        }
        pieces[q].flipH();
      }
      pieces[q].rotate();
    }
    used[q] = false;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  for (int q = 0; q < SZ*SZ; q++) {
    cin >> pieces[q].id;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> pieces[q].grid[i][j];
      }
    }
    cout << "id = " << pieces[q].id << '\n';
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cout << pieces[q].grid[i][j];
      }
      cout << '\n';
    }
    cout << '\n';
  }
  go(0,0);
  BigPiece bp;
  for (int i = 0; i < SZ; i++) {
    for (int j = 0; j < SZ; j++) {
      cout << board[i][j].id << '\n';
      for (int ii = 1; ii < N-1; ii++) {
        for (int jj = 1; jj < N-1; jj++) {
          int x = i*(N-2)+ii-1;
          int y = j*(N-2)+jj-1;
          bp.grid[x][y] = board[i][j].grid[ii][jj];
          cout << board[i][j].grid[ii][jj];
        }
        cout << '\n';
      }
      cout << '\n';
    }
  }
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      cout << bp.grid[i][j];
    }
    cout << '\n';
  }
  string monster[3] = {
    "                  # ",
    "#    ##    ##    ###",
    " #  #  #  #  #  #   ",
  };
  int total = bp.total();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      int cnt = bp.cnt(monster);
      cout << cnt << ' ' << total-15*cnt << '\n';
      bp.flipH();
    }
    bp.rotate();
  }
}
