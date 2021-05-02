import java.util.*;
import java.io.*;

class Main {
  static int N, Tmax;
  static int[] d;
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new FileReader("cowdance.in"));
    StringTokenizer st = new StringTokenizer(br.readLine());
    N = Integer.parseInt(st.nextToken());
    Tmax = Integer.parseInt(st.nextToken());
    d = new int[N];
    for (int i = 0; i < N; i++) {
      d[i] = Integer.parseInt(br.readLine());
    }

    //binary search
    int lo = 0;
    int hi = N;
    while (lo + 1 < hi) {
      int mid = (lo+hi)/2;
      if (check(mid)) {
        hi = mid;
      }
      else {
        lo = mid;
      }
    }
    
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cowdance.out")));
    out.println(hi);
    out.close();
  }

  static boolean check(int K) {
    assert(K > 0);
    int nextAvailableTime = 0;    
    //default comparator is min
    PriorityQueue<Integer> pq = new PriorityQueue<Integer>();
    for (int i = 0; i < N; i++) {
      if (pq.size() == K) {
        nextAvailableTime = pq.poll();
      }
      //check if this current cow will finish in time
      if (nextAvailableTime + d[i] > Tmax) {
        return false;
      }
      else {
        pq.add(nextAvailableTime + d[i]);
      }
    }
    return true;
  }
}

