import java.util.*;
import java.io.*;

class Main {
  static int[] dx = {0,1,0,-1};
  static int[] dy = {1,0,-1,0};
  static boolean[][] in = new boolean[3000][3000];
  static Queue<Point> q = new LinkedList<>();
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    int N = Integer.parseInt(br.readLine());
    int ans = 0;
    for (int i = 1; i <= N; i++) {
      StringTokenizer st = new StringTokenizer(br.readLine());
      int x = Integer.parseInt(st.nextToken()); x += 1000;
      int y = Integer.parseInt(st.nextToken()); y += 1000;
      Point p = new Point(x,y);
      q.add(p);
      
      while (!q.isEmpty()) {
        Point pp = q.poll();
        if (!in[pp.x][pp.y]) {
          ans++;
          in[pp.x][pp.y] = true;
          comfortable(pp);
          for (int k = 0; k < 4; k++) {
            int nx = pp.x + dx[k];
            int ny = pp.y + dy[k];
            comfortable(new Point(nx,ny));
          }
        }
      }
      System.out.println(ans-i);
    }
  }

  static void comfortable(Point p) {
    if (!in[p.x][p.y]) return;
    int cnt = 0;
    for (int k = 0; k < 4; k++) {
      int nx = p.x + dx[k];
      int ny = p.y + dy[k];
      if (in[nx][ny]) cnt++;
    }
    if (cnt == 3) {
      for (int k = 0; k < 4; k++) {
        int nx = p.x + dx[k];
        int ny = p.y + dy[k];
        if (!in[nx][ny]) 
          q.add(new Point(nx,ny));
      }
    }
  }

  static class Point {
    int x;
    int y;
    Point(int x, int y) {
      this.x = x;
      this.y = y;
    }
  }
}
