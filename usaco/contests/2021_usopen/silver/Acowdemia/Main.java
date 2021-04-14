import java.util.*;
import java.io.*;

class Main {
  static int[] c;
  static int N, K, L;
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(br.readLine());
    N = Integer.parseInt(st.nextToken());
    K = Integer.parseInt(st.nextToken());
    L = Integer.parseInt(st.nextToken());
    c = new int[N];
    st = new StringTokenizer(br.readLine());
    for (int i = 0; i < N; i++) {
      c[i] = Integer.parseInt(st.nextToken());
    }
    //binary search
    int lo = 0, hi = N+1;
    while (lo + 1 < hi) {
      int mid = (lo+hi)/2;
      if (check(mid)) {
        lo = mid;
      }
      else {
        hi = mid;
      }
    }
    System.out.println(lo);
  }

  static boolean check(int h) {
    int cnt = 0; //# of papers with citation count >= h
    ArrayList<Integer> l = new ArrayList<>();
    for (int i = 0; i < N; i++) {
      if (c[i] >= h) cnt++;
      else l.add(h-c[i]);
    }
    Collections.sort(l);
    if (cnt >= h) return true;
    else {
      int need = h-cnt;
      if (l.size() < need) return false;
      if (l.get(need-1) > K) return false;
      long sum = 0;
      for (int i = 0; i < need; i++) {
        sum += l.get(i);
      }
      return sum <= (long)K*L;
    }
  }
}
